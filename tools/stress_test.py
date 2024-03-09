from pathlib import Path
from subprocess import run
from sys import stderr
from time import time_ns as clock


class StressTest:

    def __init__(self, bad: Path, good: Path, gen) -> None:
        self._bad = bad
        self._good = good
        self._gen = gen

    def test(self):
        itr = 1
        while True:
            print(f'Stress testing: case {itr}... ', end='', file=stderr)
            inp = self._gen(clock()).encode('utf8')
            p_bad = run(self._bad, input=inp, capture_output=True, timeout=2)
            p_good = run(self._good, input=inp, capture_output=True, timeout=2)
            if p_good.returncode != 0 or p_bad.returncode != 0:
                print('\nNon-zero exit code.', file=stderr)
                print(f'\nbad: {p_bad.stderr.decode()}', file=stderr)
                print(f'\ngood: {p_good.stderr.decode()}', file=stderr)
                break
            if p_good.stdout.rstrip() != p_bad.stdout.rstrip():
                print(inp.decode())
                print('good')
                print(p_good.stdout.decode())
                print('bad')
                print(p_bad.stdout.decode())
                print('FAIL', file=stderr)
                break
            print('PASS', end='\r', file=stderr)
            itr += 1
