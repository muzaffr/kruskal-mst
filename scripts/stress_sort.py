#!/usr/bin/env python3

from pathlib import Path

from sys import path as syspath
from os import path as ospath
parpath = ospath.abspath(ospath.join(ospath.dirname(__file__), ospath.pardir))
syspath.append(parpath)
from tools.stress_test import StressTest
from tests.sort.gen import gen as gen_sort
syspath.remove(parpath)

def main():
    st = StressTest(
        Path('bin/sort_orig'),
        Path('bin/sort_stl_sort'),
        lambda seed: gen_sort(10**4, 10**9, seed),
    )
    st.test()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nScript terminated.')
    except EOFError:
        print('Input terminated.')
