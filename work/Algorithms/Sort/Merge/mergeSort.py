def merge(l1,l2):
    final=[]
    l1 = sorted(l1) 
    l2 = sorted(l2)
    while l1 and l2:
        if l1[0]<=l2[0]:
            final.append(l1.pop(0))
        else:
            final.append(l2.pop(0))
    return final+l1+l2
	
def mergesort(List):
    mid=int(len(List)/2)
    if len(List)<=1:return List
    return merge(mergesort(List[:mid]),mergesort(List[mid:]))
	
a=[545,3,4,5674,43,2223,5,90,109]
print mergesort(a)