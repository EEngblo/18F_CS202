T = int(input())

for i in range(T):
    S = input()
    answer = ""
    b = 0
    bucket = []
    for k in range(10):
        bucket.append(0)
    
    for k in range(len(S)):
        bucket[int(S[k])] += 1

    for k in range(10):
        if bucket[k] != 0:
            b = k
            bucket[k] -= 1
            break

    for k in reversed(range(10)):
        for j in range(bucket[k]):
            answer += str(k)

    print(int(answer) + b)

    

