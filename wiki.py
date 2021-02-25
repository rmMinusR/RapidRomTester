import tester
import numpy

header = "|_. Title|_. Year released|_. Filename|_. Status|"
line_fmt = "|{title}|{year}|{path}|{status}|"
test_fmt = lambda b: "Working" if b else "Not working"

def did_tests_pass(test) -> bool:
	global test_fmt
	return test_fmt(test["load"    ] == tester.TestResult.Pass \
				and test["video"   ] == tester.TestResult.Pass)
				#and test["controls"] == tester.TestResult.Pass
				#and test["audio"   ] == tester.TestResult.Pass

def format_one(rom_path:str, multicore_tests) -> str:
	global line_fmt

	data = {"title":rom_path.split("\\")[-1], "year":"", "path":rom_path.split("\\")[-1], "status": '|'.join([did_tests_pass(i) for i in multicore_tests])}

	return line_fmt.format(**data)

def format_all(*multicore_results) -> str:
	global header

	rom_list = multicore_results[0].keys()

	tests_by_rom = {}
	for k in rom_list:
		tests_by_rom[k] = [core_result[k] for core_result in multicore_results]

	return header + '\n'.join([format_one(rom, tests_by_rom[rom]) for rom in rom_list])