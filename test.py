class Solution:
    def Fibb(self, n):
        if n<=2: 
            return 1
        else:
            return self.Fibb(n-1) + self.Fibb(n-2)
        
    def findMinFibonacciNumbers(self, k: int) -> int:
        for x in range(k):
            for y in range(k):
                if self.Fibb(y) == k: return 1
                if self.Fibb(x) + self.Fibb(y) == k:
                    return 2
                
        x = 0
        while self.Fibb(x) <=k:
            if self.findMinFibonacciNumbers(k-x) != -1:
                return self.findMinFibonacciNumbers(k-x) + 1
            x+=1
                
        return -1

sol = Solution  ()
print(sol.findMinFibonacciNumbers(19641))