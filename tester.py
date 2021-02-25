from time import sleep
import numpy # For image manipulation
import imageio # For thumbnail generation
from subprocess import Popen, PIPE
from pywinauto.keyboard import send_keys as _send_keys
from pywinauto.application import Application
import os, os.path
import config

from enum import Enum
class TestResult(Enum):
    NotRun = 0
    Pass = 1
    Fail = 2
    Inconclusive = 3

def trailingslash(it):
    """Add a trailing slash if none exists"""
    return it if it[-1]=="/" or it[-1]=="\\" else it+"/"


def retroarch_launch(rom_path, core_path, retroarch_path):
    """Launch a RetroArch process and return the pywinauto wrapper"""
    process = Popen([retroarch_path, "--appendconfig", config.config_overrides_path, "-L", core_path, rom_path], stdout=PIPE, stderr=PIPE)
    return (process, Application().connect(process=process.pid))


def take_screenshot(window) -> numpy.array:
    window.set_focus()
    return numpy.array(window.capture_as_image())[51:-8, 9:-8] # (8, 51) to (-8, -8) -> YY XX

def send_input(key):
    _key = key[1:-1] if key[0] == "{" and key[-1] == "}" else key
    
    _send_keys("{"+_key+" down}")
    sleep(0.05)
    _send_keys("{"+_key+" up}")

def test_pair(rom_path, core_path, retroarch_path, thumbnail_dir:str=None, start_btn:str="{ENTER}", startup_time=2):
    """Run all tests for the given rom/core pair"""

    rom_name  : str = ".".join(rom_path .split("\\")[-1].split(".")[:-1])
    core_name : str = ".".join(core_path.split("\\")[-1].split(".")[:-1])
    
    proc: Popen
    retroarch: Application
    proc, retroarch = retroarch_launch(rom_path, core_path, retroarch_path)
    
    results = {"load":     TestResult.NotRun,
               "video":    TestResult.NotRun,
               "audio":    TestResult.NotRun,
               "controls": TestResult.NotRun}
    
    sleep(0.25)
    try:
        
        
        ########################## TEST SECTION: LOAD ##########################
    
        #If RetroArch failed to start, report inconclusive
        #If RetroArch CPU usage is below threshold, core probably failed to load
        #If no windows opened, core probably failed to load
        if not retroarch.is_process_running() or retroarch.cpu_usage(interval=2) < 0.2 or len(retroarch.windows()) < 1:
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
        
        screencap_1: numpy.array
        screencap_2: numpy.array

        try:
            #Do screengrab
            screencap_1 = take_screenshot(retroarch_window)
            sleep(startup_time) #Just in case there's a loading splash
            screencap_2 = take_screenshot(retroarch_window)
    
            #Save a thumbnail
            if thumbnail_dir != None:
                imageio.imwrite(trailingslash(thumbnail_dir)+rom_name+".png", screencap_2)
    
            #Check to see if the frame has anything in it, or if there is a significant difference (i.e. motion)
            v = numpy.var((screencap_2-screencap_1).flatten()) + numpy.var(screencap_1.flatten()) + numpy.var(screencap_2.flatten())
            if v > 1500:
                results["video"] = TestResult.Pass
            else:
                results["video"] = TestResult.Fail
                return results
        except Exception as e:
            results["video"] = TestResult.Inconclusive
            return results
    

        ########################## TEST SECTION: CONTROLS ##########################
    
        send_input(start_btn) #Start
        sleep(2)
        screencap_3: numpy.array = take_screenshot(retroarch_window)
        v = numpy.var((screencap_3-screencap_2).flatten())
        results["controls"] = TestResult.Pass if v > 1500 else TestResult.Fail # UNRELIABLE if splash screen is animated
    

        ########################## TEST SECTION: AUDIO ##########################
    
        # Not yet implemented...


    finally:
        #Cleanup
        retroarch.kill(soft=False)
        proc.kill()
    return results

def test_dir(rom_dir, core_path, retroarch_path, thumbnail_dir:str=None, start_btn:str = "{ENTER}", startup_time=2):
    roms: list[str] = [f for f in [os.path.join(rom_dir, f) for f in os.listdir(rom_dir)] if os.path.isfile(f)]
    rv = {}
    for rom_path in roms:
        rv[rom_path] = test_pair(rom_path, core_path, retroarch_path, thumbnail_dir, start_btn, startup_time)
    return rv

if __name__ == "__main__":
    raise AssertionError("Must be imported")