from enum import Enum
class TestResult(Enum):
    Unknown = 0
    Pass = 1
    Fail = 2
    RequirementsNotMet = 3


def safearg(s):
    """Make an object safe by enclosing it in quotes"""
    out = s
    if out[0] != "\"":
        out = "\""+out
    if out[-1] != "\"":
        out += "\""
    return out


def trailingslash(it):
    """Add a trailing slash if none exists"""
    return it if it[-1]=="/" or it[-1]=="\\" else it+"/"


from pywinauto.application import Application
def retroarch_launch(rom_path, core_path, retroarch_path):
    """Launch a RetroArch process and return the pywinauto wrapper"""
    return Application().start(
                      safearg(retroarch_path) # retroarch.exe
              +" -L "+safearg(core_path)      # Specify core
                 +" "+safearg(rom_path)       # Specify ROM
    )


def take_screenshot(window):
    window.set_focus()
    return numpy.array(window.capture_as_image())[51:-8, 9:-8] # (8, 51) to (-8, -8) -> YY XX


from pywinauto.keyboard import send_keys as _send_keys
def send_input(key):
    _key = key[1:-1] if key[0] == "{" and key[-1] == "}" else key
    
    _send_keys("{"+_key+" down}")
    sleep(0.05)
    _send_keys("{"+_key+" up}")


from time import sleep
import numpy # For image manipulation
from scipy.misc import imsave # For thumbnail generation
def test(rom_path, core_path, retroarch_path, thumbnail_dir):
    """Run all tests for the given rom/core pair"""

    rom_name  = ".".join(rom_path .split("\\")[-1].split(".")[:-1])
    core_name = ".".join(core_path.split("\\")[-1].split(".")[:-1])
    
    retroarch = retroarch_launch(rom_path, core_path, retroarch_path)
    
    results = {"load":     TestResult.Unknown,
               "video":    TestResult.RequirementsNotMet,
               "audio":    TestResult.RequirementsNotMet,
               "controls": TestResult.RequirementsNotMet}
    
    sleep(0.25)
    
    ########################## TEST SECTION: LOAD ##########################
    
    #If RetroArch failed to start, report inconclusive
    if not retroarch.is_process_running():
        results["load"] = TestResult.Fail
        return results
    #If RetroArch CPU usage is below threshold, core probably failed to load
    elif retroarch.cpu_usage(interval=2) < 0.2:
        results["load"] = TestResult.Fail
        return results
    #If no windows opened, core probably failed to load
    elif len(retroarch.windows()) < 1:
        results["load"] = TestResult.Fail
        return results
    else:
        results["load"] = TestResult.Pass
    
    retroarch_window = retroarch.top_window()
    
    #Just in case there are loading splashes...
    retroarch_window.set_focus()
    send_input("{ENTER}")
    
    #Wait 4 seconds for the modal to disappear
    sleep(2)
    
    ########################## TEST SECTION: VIDEO ##########################
    
    #Do screengrab
    screencap_1 = take_screenshot(retroarch_window)
    sleep(2) #Just in case there's a loading splash
    screencap_2 = take_screenshot(retroarch_window)
    
    #Save a thumbnail
    imsave(trailingslash(thumbnail_dir)+rom_name+".png", screencap_2)
    
    #Check to see if the frame has anything in it, or if there is a significant difference (i.e. motion)
    v = numpy.var((screencap_2-screencap_1).flatten()) + numpy.var(screencap_1.flatten()) + numpy.var(screencap_2.flatten())
    if v > 1500:
        results["video"] = TestResult.Pass
    else:
        results["video"] = TestResult.Fail
        return results
    
    ########################## TEST SECTION: CONTROLS ##########################
    
    send_key("{ENTER}") #Start
    sleep(2)
    screencap_3 = take_screenshot(retroarch_window)
    v = numpy.var((screencap_3-screencap_2).flatten())
    results["controls"] = TestResult.Pass if v > 1500 else TestResult.Fail # UNRELIABLE if splash screen is animated
    
    ########################## TEST SECTION: AUDIO ##########################
    
    #Cleanup
    retroarch.kill(soft=False)
    return results

