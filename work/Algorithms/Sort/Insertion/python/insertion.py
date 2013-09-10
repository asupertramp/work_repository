def insertion_sort(n):
    if len(n) == 1:
        return n
    b = insertion_sort(n[1:])
    m = len(b)
    for i in range(m):
        if n[0] <= b[i]:
            return b[:i]+[n[0]]+b[i:]
    return b + [n[0]]
	
test=[10,9,8,7,6,5,4]
result=insertion_sort(test)
print result