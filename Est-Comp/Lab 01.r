#site: https://posit.cloud/content/8511940

#operações básicas
2+2 #adição
1-10 #subtração
2*87 #produto
34/21 #divisão
3**6 #potenciação
3^6 #potenciação
#====================================================================
a <- 123*98 #cria objetos
a_1 <- 123*98 #cria objetos
class(a)
12+1245 -> b #cria objetos
w <- "furiosa"
class(w)
y <- TRUE #ou T
class(y)
#====================================================================
TRUE + FALSE
TRUE + TRUE
FALSE + FALSE
#====================================================================
#vetores
x <- c(23,10,45)
x
d <- c(x,45)
d+c(TRUE,FALSE)
# 23 10 45
#T F T F
x[c(2,3,3)]
x < 30
sum(x<30)#somando T + T + F
x[x<30]
which(x<30)
c(12,34,"cruzeiro")
23:10345
p<-23:10345
p[14]


dado1 <- sample(x = 1:6 ,size = 1000000, replace = TRUE)
dado1
#dado1[dado1==3]
sum(dado1 == 3)/1000000
mean(dado1 == 3) #media que o 3 apareceu com relação aos 10000 lançamentos

dado2 <- sample(x = 1:6 ,size = 1000000, replace = TRUE)
soma <- dado1+dado2
soma[1:10]
mean(soma==3)






###################################REVISÂO###################################
#operações basicas

2+5 #soma
2-4 #subtração
5*7 #multiplicação
8/2 #divisão
8**2 #potencia
10%%3 #resto


#atribuindo valores

a <- 3*2
4*3 -> b
resultado = a + b
d <- TRUE
calss(d)
TRUE + TRUE #=2
TRUE + FALSE #=1
FALSE + FALSE #=0
TRUE/FALSE #=Inf
v1 <- 90+3
x <- "teste"
class(x)


#criando vetores

x2 <- c(3,10,78)
length(x2)
sum(x2)
mean(x2)
c2 <- c(1,6,"teste")
x2[c(2,3)]
x3 <- c(x2,67,90)
x3 < 70 #numeros menores que 70 no vetor x3
sum(x3<70) #soma os valores abaixo de 70
x3[x3<70] #filtra o vetor parar os numeros menores que 70
sum(x3[x3<70]) #soma os numeros menores que 70

TRUE | FALSE #ou
TRUE & FALSE #e


#criando um dado
?sample
sample(10)
dado1 <- sample(x = 1:6 ,size = 1000000, replace = TRUE) #replace=TRUE é pra quando vc tira, coloca dvolta
dado1
#dado1[dado1==3]
sum(dado1 == 3)/1000000
mean(dado1 == 3) #media que o 3 apareceu com relação aos 10000 lançamentos
barplot(table(dado1))
