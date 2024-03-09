from random import randint, choice, seed

def gen(size: int, queries: int, width: int, seed_: int):
    '''Generate an input of size and width for priority_queue.'''
    ret = f'{size} {queries}\n'
    cur = size  # the current size of the heap, grows and shrinks with the ops
    seed(seed_)
    for _ in range(size):
        ret += f'{randint(-width, width)} '
    ret += '\n'
    for _ in range(queries):
        op = 'i'
        if cur >= 1:
            op = choice('irp')
        if op == 'i':
            ret += f'i {randint(-width, width)}\n'
            cur += 1
        elif op == 'r':
            ret += 'r\n'
            cur -= 1
        elif op == 'p':
            ret += 'p\n'
    return ret

def main():
    # TODO: implement argument parser
    pass

if __name__ == '__main__':
    main()
