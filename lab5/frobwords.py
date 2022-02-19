#!/usr/bin/env python3
import argparse
import random

def frobwords(s):
    fwords = []
    frobd = ""
    for word in s:
        for ch in word:
            if(ch != '\n' and ch != ' '):
                frobd += chr(ord(ch) ^ 0x2A)
            else:
                break
        fwords.append(frobd)
        frobd = ""
    return fwords



def gen_sen(f_file, ln_count):
    words = (
        "adorable",
        "alpha",
        "alphabet",
        "barfs",
        "blank",
        "beta",
        "car",
        "clueless",
        "computer",
        "computers",
        "crazily",
        "gamma",
        "tau",
        "Sigma",
        "Sigma",
        "  dusty  trail ",
        "drives",
        "dutifully",
        """
        foolishly
        """,
        "girl",
        "hits",
        "jumps",
        "jumping",
        "jumped",
        """keyboard
        """,
        "light-house aardvark",
        """
        lines""",
        "mathematics",
        "merrily",
        "monkey",
        "money",
        "Money",
        "occasionally",
        "odd",
        "r@nd0m ⊆h^R$",
        "RA|\|DoM c!-!aRs*",
        "pi",
        "Pi"
        "puppy",
        "rabbit",
        "runs",
        "rusty                  ",
        "sigma",
        "stupid",
        "testing",
        "zeta"
    )

    fwords = frobwords(words)

    with open(f_file,'w') as f:
        for i in range(ln_count):
            f.writelines(' '.join(random.choices(fwords, k = len(fwords))))
            f.write("\n")



if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("f_file", metavar="f_file", type=str, help="name of the file to store frobd words")
    parser.add_argument("ln_count", metavar="ln_count", type=int, help="total number of words to be printed")
    args = parser.parse_args()
    gen_sen(args.f_file, args.ln_count)
