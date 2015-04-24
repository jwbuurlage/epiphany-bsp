#!/usr/bin/python3
import re
import subprocess
import os

EXPECT_PATTERN = re.compile(r'// expect: (.*)')

#Assuming that Makefile contains list of all unit-tests

def get_contents(location):
    f = open(location)
    result = f.read()
    f.close()
    return result

def run_unit_test(unit_test):
    output=""
    try:
        output = subprocess.check_output(["bin/host_"+unit_test, "Hello World!"], stderr=subprocess.STDOUT, universal_newlines=True)
    except OSError:
        print("OSError")    #When running on non-epiphany system
    return output

def do_unit_test(unit_test):
    host_srctext = get_contents("./"+unit_test+"/host_"+unit_test+".c")
    host_expected_outputs = re.findall(EXPECT_PATTERN, host_srctext)

    e_srctext = get_contents("./"+unit_test+"/e_"+unit_test+".c")
    e_expected_outputs = re.findall(EXPECT_PATTERN, e_srctext)

    expected_output = "\n".join(host_expected_outputs)+"\n".join(e_expected_outputs);
    actual_output = run_unit_test(unit_test)

    print("TESTING:" + unit_test)
    print("GOT : " + actual_output)
    print("WANT: " + expected_output)
    

maketext = get_contents("Makefile")
matches = re.search('all: (.*)\\n', maketext)
unit_tests = matches.group(1).split()

for unit_test in unit_tests:
    do_unit_test(unit_test)
