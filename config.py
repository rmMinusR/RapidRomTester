# Shortcut reading

import win32com.client

_shell = None
def get_shortcut_target(path) -> str:
	global _shell
	if _shell == None:
		_shell = win32com.client.Dispatch("WScript.Shell")
	return _shell.CreateShortCut(path).Targetpath

# Detect values

import os.path

data_path: str = get_shortcut_target(os.path.expanduser(r"~\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\RetroArch\RetroArch Data Folder.lnk"))
exe_path: str = get_shortcut_target(os.path.expanduser(r"~\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\RetroArch\RetroArch.lnk"))

rom_folder_path	: str = os.path.join(data_path, "downloads", "")
core_folder_path: str = os.path.join(data_path, "cores", "")

# Reference to the retroarch-config-overrides.cfg file

config_overrides_path = os.path.join(os.path.dirname(os.path.realpath(__file__)), "retroarch-config-overrides.cfg")