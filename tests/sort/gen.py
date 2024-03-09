from random import randint, seed

def gen(size: int, width: int, seed_: int):
    '''Generate an input of size and width for sort.'''
    ret = f'{size}\n'
    seed(seed_)
    for _ in range(size):
        ret += f'{randint(-width, width)} '
    return ret

def main():
    # TODO: implement argument parser
    pass

if __name__ == '__main__':
    main()
