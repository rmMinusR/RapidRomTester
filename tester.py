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

def getTasks(name):
    r = os.popen('tasklist /v /fi "IMAGENAME eq '+name+'"').read().strip().split('\n')
    for i in r:
        if name in i:
            return i
    return None

def isAlive(name):
    r = getTasks(name)
    return r != None and not "Not Responding" in r

def ensureAlive():
    if not isAlive("retroarch.exe"):
        raise Exception("ERROR: RetroArch dead or unresponsive")
    else:
        return

def retroarch_launch(rom_path, core_path, retroarch_path):
    """Launch a RetroArch process and return the pywinauto wrapper"""
    process = Popen([retroarch_path, "--appendconfig", config.config_overrides_path, "-L", core_path, rom_path])
    return (process, Application().connect(process=process.pid))


def take_screenshot(window) -> numpy.array:
    ensureAlive()
    return numpy.array(window.capture_as_image())[51:-8, 9:-8] # (8, 51) to (-8, -8) -> YY XX

def send_input(key):
    _key = key[1:-1] if key[0] == "{" and key[-1] == "}" else key
    
    _send_keys("{"+_key+" down}")
    sleep(0.05)
    _send_keys("{"+_key+" up}")

def test_pair(rom_path, core_path, retroarch_path, thumbnail_dir:str=None, start_btns:tuple=("{ENTER}",), startup_time=2):
    """Run all tests for the given rom/core pair"""

    rom_name  : str = ".".join(rom_path .split("\\")[-1].split(".")[:-1])
    core_name : str = ".".join(core_path.split("\\")[-1].split(".")[:-1])
    
    print("Testing "+rom_name+" / "+core_name+"...")

    proc: Popen
    retroarch: Application
    proc, retroarch = retroarch_launch(rom_path, core_path, retroarch_path)

    results = {"load":     TestResult.NotRun,
               "video":    TestResult.NotRun,
               "audio":    TestResult.NotRun,
               "controls": TestResult.NotRun}
    
    sleep(2)
    try:
        
        
        ########################## TEST SECTION: LOAD ##########################
    
        #If RetroArch failed to start, report inconclusive
        #If RetroArch CPU usage is below threshold, core probably failed to load
        #If no windows opened, core probably failed to load
        if   retroarch.is_process_running() \
         and retroarch.cpu_usage(interval=2) > 2.0 \
         and len(retroarch.windows()) > 0:
            results["load"] = TestResult.Pass
            print("Load test PASS")
        else:
            results["load"] = TestResult.Fail
            print("Load test FAIL")
            return results
        
        ensureAlive()
        retroarch_window = retroarch.top_window()
        retroarch_window.move_window(x=0, y=0)
    
        #Just in case there are loading splashes...
        send_input("{ENTER}")
    
        #Wait 4 seconds for the modal to disappear
        sleep(2)
    

        ########################## TEST SECTION: VIDEO ##########################
        
        screencaps:list[tuple[numpy.array, float]] = {}
        peak:tuple[numpy.array, float] = None

        try:
            #Do screengrabs
            for i in range(int(startup_time/0.5)):
                sc = take_screenshot(retroarch_window)
                screencaps[i] = (sc, numpy.var(sc))
                
                if peak == None or peak[1] < screencaps[i][1]:
                    peak = screencaps[i]
                
                sleep(0.5)

            deltas = [numpy.var(screencaps[i][0]-screencaps[i+1][0]) for i in range(len(screencaps)-1)]
            delta_avg = numpy.average(deltas)

            #Save a thumbnail
            if thumbnail_dir != None:
                imageio.imwrite(trailingslash(thumbnail_dir)+rom_name+".png", peak[0])
    
            #Check to see if the frame has anything in it, or if there is a significant difference (i.e. motion)
            if peak[1] > 150:
                print("Video test PASS: "+str(peak[1]))
                results["video"] = TestResult.Pass
            else:
                print("Video test FAIL: "+str(peak[1]))
                results["video"] = TestResult.Fail
                return results
        except Exception as e:
            results["video"] = TestResult.Inconclusive
            print(str(e))
            return results
    

        ########################## TEST SECTION: CONTROLS ##########################

        for i in start_btns:
            send_input(i) #Start
            sleep(0.5)
        sleep(2)
        screencap_post_start: numpy.array = take_screenshot(retroarch_window)
        v = numpy.var((screencaps[len(screencaps)-1][0]-screencap_post_start).flatten())
        threshold = numpy.average(deltas[-4:-1]) * 0.4 # Is this even reliable???
        if v > threshold:
            print("Controls test PASS: "+str(v)+" vs "+str(threshold))
            results["controls"] = TestResult.Pass
        else:
            print("Controls test FAIL: "+str(v)+" vs "+str(threshold))
            results["controls"] = TestResult.Fail
        

        ########################## TEST SECTION: AUDIO ##########################
    
        # Not yet implemented...


    finally:
        #Cleanup
        retroarch.kill(soft=False)
        proc.kill()
    return results

def test_dir(rom_dir, core_path, retroarch_path, thumbnail_dir:str=None, start_btns:tuple=("{ENTER}",), startup_time=2):
    roms: list[str] = [f for f in [os.path.join(rom_dir, f) for f in os.listdir(rom_dir)] if os.path.isfile(f)]
    rv = {}
    for rom_path in roms:
        rv[rom_path] = test_pair(rom_path, core_path, retroarch_path, thumbnail_dir, start_btns, startup_time)
    return rv

if __name__ == "__main__":
    raise AssertionError("Must be imported")