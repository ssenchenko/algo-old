"""

compute knapsack problem recursively with memoizing solved problems

"""
import sys

# pylint: disable=C0103, W0312, C0303


def get_input(file_name):
	"""
	read a file with data and output data separetly
	output:
	W - possible knapsack weight
	n - number of items available in a loot
	vals - values of the loot items
	wts - weights of the loot items
	input: file formated like that
	first row: Capacity Number_Of_Items
	second row up: Item_Value Item_Weight
	separator is a space (' ')
	"""
	lines = [x for x in open(file_name, 'r').read().split('\n')]
	if lines[-1] == '':
		lines.pop()
	W = [int(x) for x in lines[0].split(' ')][0]
	n = [int(x) for x in lines[0].split(' ')][1]
	items = [int(y) for x in lines[1:] for y in x.split(' ')] # everything in one line
	vals = items[::2] # skip every second item
	wts = items[1::2] # start from item 1 (which is second) and skip every second item
	return (W, n, vals, wts)

def rknapsack(w, j, vals, wts, cache):
	"""
	recursive knapsack problem with NO item repetition
	output: knapsack solution
	input:
	W - possible knapsack weight
	n - number of items available in a loot
	vals - values of the loot items
	wts - weights of the loot items
	cache - dictionary to cache alredy calculated results
	"""
	# print reecursive stack for debugging
	# print("knapsack(" + str(w) + ", " + str(j) + ")\n")
	# base case
	if j < 0:
		return 0
	# if the subproblem has been computed, use it
	if cache.get((w, j)):
		return cache[(w, j)]
	# if weight of current element is more than W
	# element cannot be included, proceed with next one
	if wts[j] > w:
		K = rknapsack(w, j - 1, vals, wts, cache)
	# recursively calculate maximum
	else:
		K = max(rknapsack(w, j - 1, vals, wts, cache), rknapsack(w - wts[j], j - 1, vals, wts, cache) + vals[j])
	
	cache[(w, j)] = K
	return K

def knapsack(W, n, vals, wts):
	"""
	iterative knapsack problem with NO item repetition
	output: knapsack solution
	input:
	W - possible knapsack weight
	n - number of items available in a loot
	vals - values of the loot items
	wts - weights of the loot items
	"""
	K = [[0 for x in range(n)] for x in range(W + 1)]
	for j in range(n):
		for w in range(1, W + 1):
			if wts[j] > w:
				K[w][j] = K[w][j - 1]
			else:
				K[w][j] = max(K[w][j - 1], K[w - wts[j]][j - 1] + vals[j])
	return K[-1][-1]

def knapsack_rep(W, n, vals, wts):
	"""
	iterative knapsack problem with item repetition allowed
	output: knapsack solution
	input:
	W - possible knapsack weight
	n - number of items available in a loot
	vals - values of the loot items
	wts - weights of the loot items
	"""
	# knapsack solutions array
	K = [0 for x in range(W + 1)]
	# it'd be useful to have values and weights sorted according the weights asc
	# first transform the lists to a list of tuples
	vals_wts = list(zip(vals, wts))
	
	# a short helper function that returns the key to sort
	def get_key(item):
		"""
		a short helper function that returns the key to sort
		"""
		return item[1]
	
	# sort
	vals_wts = sorted(vals_wts, key=get_key)
	# transform it back to 2 lists
	wts = [x[1] for x in vals_wts]
	vals = [x[0] for x in vals_wts]
	
	for w in range(1, W + 1):
		j = 0
		while j < n and wts[j] <= w:
			if K[w] < K[w - wts[j]] + vals[j]:
				K[w] = K[w - wts[j]] + vals[j]
			j += 1
	return K[-1]

# (cap, it, vs, ws) = get_input('../../test_data/knapsack_small.txt')
(cap, it, vs, ws) = get_input('../../test_data/c3w4_knapsack.txt')
# (cap, it, vs, ws) = get_input('../../test_data/c3w4_knapsack_big.txt')
# best0 = knapsack_rep(cap, it, vs, ws)
# best1 = knapsack(cap, it, vs, ws)
sys.setrecursionlimit(10000) # default is sys.getrecursionlimit = 10000
cache = {}
best2 = rknapsack(cap, it - 1, vs, ws, cache)

# print(best1, best2)
print(best2)
