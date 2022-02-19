import os
import sys


class CommitNode:
	def __init__(self, commit_hash):
		"""
		:type commit_hash: str
		"""
		self.commit_hash = commit_hash
		self.parents = set()
		self.children = set()


def populate_stack(b_list, h_path):
	for branch in b_list:
		if not os.path.isdir(h_path+"/"+branch):
			with open((h_path + "/" + branch), "r") as br:
				commit = br.read().rstrip('\n')
				stack.append(commit)

				if commit not in visited.keys():
					visited[commit] = CommitNode(commit)

				if commit not in heads.keys():
					heads[commit] = branch
				else:
					heads[commit] += " " + branch
		else:
			new_path = h_path + "/" + branch
			new_list = os.listdir(new_path)
			populate_stack(new_list, new_path)


############################################################################


stack = []
visited = {}
heads = {}
found = False


if len(sys.argv) == 1:
	current_path = os.getcwd()
else:
	current_path = sys.argv[1]

if not os.path.isdir(current_path):
	sys.stderr.write("error: argument must be a directory. exiting\n")
	exit(1)


while current_path:
	current_dir = os.listdir(current_path)
	if ".git" in current_dir:
		found = True
		break
	else:
		current_path = current_path.rsplit('/', 1)
		current_path = current_path[0]


if not found:
	sys.stderr.write("Not inside a Git repository\n")
	exit(1)


head_path = current_path + "/.git/refs/heads"
branch_list = os.listdir(head_path)


populate_stack(branch_list, head_path)


#print(stack)
#print(heads)

for key in heads:
	print(key, heads[key])
