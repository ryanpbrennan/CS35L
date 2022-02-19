#!/usr/bin/python

import random, sys, argparse


class shuffleStuff:
    def __init__(self, filename, inputrange, headcount, repeat):
        if (filename == "-" or filename is None) and inputrange is None:
            self.lines = sys.stdin.readlines()
            
            if (len(self.lines) < 1): return None

        elif (inputrange is None):
            f = open(filename, 'r')
            self.lines = f.readlines()
            f.close()
    
            if (len(self.lines) < 1): return None
        
        self.headcount = headcount
        self.inputrange = inputrange
        self.repeat = repeat

    def shuffle(self):
        if self.repeat and self.inputrange is not None and \
                                                self.headcount is not None:
            newrange = []
            for i in range(self.inputrange[0], self.inputrange[1]+1):
                newrange.append(i)
            random.shuffle(newrange)
            for i in range(0, self.headcount):
                curInt = random.randint(0, len(newrange)-1)
                print(newrange[curInt])

        elif self.repeat and self.inputrange is None and \
                                                self.headcount is not None:
            random.shuffle(self.lines)
            for i in range(0, self.headcount):
                curInt = random.randint(0, len(self.lines)-1)
                sys.stdout.write(self.lines[curInt])

        elif not self.repeat and self.inputrange is not None and \
                                                self.headcount is not None:
            newrange = []
            for i in range(self.inputrange[0], self.inputrange[1]+1):
                newrange.append(i)
            random.shuffle(newrange)
            if self.headcount <= len(newrange):
                for i in range(0, self.headcount):
                    print(newrange[i])
            else: 
                for i in range(0, len(newrange)):
                    print(newrange[i])

        elif not self.repeat and self.inputrange is None and \
                                                self.headcount is not None:
            random.shuffle(self.lines)
            if self.headcount >= len(self.lines):
                for i in range (0, len(self.lines)):
                    sys.stdout.write(self.lines[i])
            else:
                for i in range (0, self.headcount):
                    sys.stdout.write(self.lines[i])

        elif self.repeat and self.inputrange is not None and \
                                                self.headcount is None:
            newrange = []
            for i in range(self.inputrange[0], self.inputrange[1]+1):
                newrange.append(i)
            random.shuffle(newrange)
            for i in range(0, len(newrange)):
                curInt = random.randint(0, len(newrange)-1)
                print(newrange[curInt])

        elif self.repeat and self.headcount is None and \
                                                    self.inputrange is None:
            while self.repeat:
                random.shuffle(self.lines)
                for line in self.lines:
                    sys.stdout.write(line)
                    
        elif not self.repeat and self.inputrange is not None and \
                                                    self.headcount is None:
            newrange = []
            for i in range(self.inputrange[0], self.inputrange[1]+1):
                newrange.append(i)
            random.shuffle(newrange)
            for i in range(0, len(newrange)):
                print(newrange[i])

        else:
            random.shuffle(self.lines)
            for line in self.lines:
                sys.stdout.write(line)


def main():

    parser = argparse.ArgumentParser()
    parser.add_argument("input_file", default=None, nargs='?')
    parser.add_argument("-i","--input-range", type=str, 
                        metavar="LO-HI", help="shuffle range from LO to HI")
    parser.add_argument("-n","--head-count", type=int, nargs=1,
                        metavar="NUM", help="output at most NUM lines.\
                        When combined with -r, outputs NUM lines of file\
                        or stdin NUM times")
    parser.add_argument("-r","--repeat", action="store_true")

    args = parser.parse_args()

    ir = []
    if args.input_range is not None: 
        pre = args.input_range.split('-')
        for inx, item in enumerate(pre):
            ir.append(int(item))

        if ir[1] <= ir[0] or ir[0] < 0:
            raise argparse.ArgumentTypeError('invalid range.')
    else:
        ir = None

    if args.head_count is not None and args.head_count[0] >= 0:    
        hc = int(round((args.head_count[0])))
    elif args.head_count is not None and args.head_count[0] < 0:
        raise argparse.ArgumentTypeError('headcount must be positive')
    else:
        hc = None

    rp = args.repeat
    fi = args.input_file

    test = shuffleStuff(fi, ir, hc, rp)
    test.shuffle()

if __name__ == "__main__":
    main()
