def solve():
    t = int(input())
    for _ in range(t):
        n, m = map(int, input().split())
        queries = []
        for _ in range(2 * m):
            l, r = map(int, input().split())
            queries.append((l, r))
        
        # Пробуем несколько простых стратегий
        strategies = []
        
        # Стратегия 1: первые два элемента одинаковые (позиции 1,2)
        strategies.append((1, 2))
        
        # Стратегия 2: последние два элемента одинаковые (позиции n-1,n)
        if n >= 2:
            strategies.append((n-1, n))
        
        # Стратегия 3: элементы в середине одинаковые
        if n >= 3:
            strategies.append((1, 3))
            strategies.append((2, 4))
        
        # Стратегия 4: крайние элементы одинаковые
        if n >= 3:
            strategies.append((1, n))
        
        found = False
        for pos1, pos2 in strategies:
            if pos1 > n or pos2 > n:
                continue
                
            positive_queries = []
            negative_queries = []
            
            for i, (l, r) in enumerate(queries):
                # Запрос положительный если включает и pos1 и pos2
                if l <= pos1 and r >= pos2:
                    positive_queries.append(i)
                else:
                    negative_queries.append(i)
            
            if len(positive_queries) == m and len(negative_queries) == m:
                arr = list(range(1, n + 1))
                arr[pos2-1] = arr[pos1-1]  # делаем элементы одинаковыми
                print(' '.join(map(str, arr)))
                found = True
                break
        
        if not found:
            print(-1)

solve()