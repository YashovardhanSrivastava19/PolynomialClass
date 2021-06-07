""" [Polynomial Operations in Python] """
# Note:for most purpose,power upto 20 is more than practical. (in expDict)
class Polynomial:
    """[Base class for basic operations on Polynomials]"""
    Symbol="x"
    expDict={0:"\u2070",1:"\u00b9",2:"\u00b2",3:"\u00b3",4:"\u2074",5:"\u2075",6:"\u2076",7:"\u2077",8:"\u2078",9:"\u2079",
            10:"\u00b9\u2070",11:"\u00b9\u00b9",12:"\u00b9\u00b2",13:"\u00b9\u00b3",14:"\u00b9\u2074",15:"\u00b9\u2075",
            16:"\u00b9\u2076",17:"\u00b9\u2077",18:"\u00b9\u2078",19:"\u00b9\u2079",20:"\u00b2\u2070"}
    def __init__(self,N:int,symbol:str="x") -> None:
        self.degree=N
        self.coefficients=[0 for i in range(N+1)]
        self.Symbol=symbol    
    def InputPolynomial(self)->None:
        """[Input the coefficients of the polynomial]"""
        for i in range(self.degree+1):
            print("Input the coefficient of {}{}:".format(self.Symbol,self.expDict[i]),end="  ")
            self.coefficients[i]=int(input())
        assert self.coefficients[-1] !=0 ,"Polynomial of degree {} requires non-zero coefficient of {}{}".format(self.degree,self.Symbol,self.expDict[self.degree])    

    def PrintPoly(self)->None:
        """[Print the polynomial(different class for abstraction)]"""
        print(PrintPolynomial(self).printPoly())

    def __add__(self,other:"Polynomial")->"Polynomial":
        """[Add two polynomials]"""
        tempDegree=max(self.degree,other.degree)
        temp=Polynomial(tempDegree)
        def FillTemp(deg):
            temp.coefficients=[self.coefficients[i]+other.coefficients[i] for i in range(deg+1)]
        if self.degree==other.degree:
            FillTemp(self.degree)
        elif self.degree>other.degree:
            other.coefficients.extend(0 for i in range(other.degree,self.degree+1))
            FillTemp(self.degree)
        else:
            self.coefficients.extend(0 for i in range(self.degree,other.degree+1))
            FillTemp(other.degree)
        return temp

    def __sub__(self,other:"Polynomial")->"Polynomial":
        """[Subtract two polynomials]"""  
        tempDegree=max(self.degree,other.degree)
        temp=Polynomial(tempDegree)
        def FillTemp(deg):
            temp.coefficients=[self.coefficients[i]-other.coefficients[i] for i in range(deg+1)]
        if self.degree==other.degree:
            FillTemp(self.degree)
        elif self.degree>other.degree:
            other.coefficients.extend(0 for i in range(other.degree,self.degree+1))
            FillTemp(self.degree)
        else:
            self.coefficients.extend(0 for i in range(self.degree,other.degree+1))
            FillTemp(other.degree)
        return temp
    def __mul__(self,other:"Polynomial")->"Polynomial":
        """[Multiply two polynomials]"""
        temp=Polynomial(self.degree+other.degree)
        for i in range(self.degree+1):
            for j in range(other.degree+1):
                temp.coefficients[i+j]+=(self.coefficients[i]*other.coefficients[j])    
        return temp        
    def __repr__(self) -> str:
        """[Print polynomial object]"""
        return PrintPolynomial(self).printPoly()

class PrintPolynomial:
    """[class for polynomial typesetting]"""
    def __init__(self,Poly:Polynomial) -> None:
        self._poly=Poly

    def printPoly(self)->str:
        exprList=["{}{}{}".format(self._poly.coefficients[i],self._poly.Symbol,self._poly.expDict[i]) for i in range(self._poly.degree+1)]           
        expr="+".join(exprList)
        return expr


#Object Instantiation
Poly1=Polynomial(3,"y")
Poly1.InputPolynomial()
print(Poly1)
Poly2=Polynomial(3,"y")
Poly2.InputPolynomial()
print(Poly2)
print("Sum:\t",Poly1+Poly2)
print("Difference:\t",Poly1-Poly2)
print("Multiply:\t",Poly1*Poly2)
print("First Polynomial:\t",Poly1)
print("Second Polynomial:\t",Poly2)
