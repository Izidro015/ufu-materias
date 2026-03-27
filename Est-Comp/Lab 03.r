dados <- read.table(file = "titanic.txt", header = TRUE, sep = ",")
vivos <- sum(dados[,2])
mean(vivos)
dados$Survived <- as.factor(dados$Survived)
summary(dados)
dados$Pclass <- as.factor(dados$Pclass)
dados$Sex <- as.factor(dados$Sex)
summary(dados)
str(dados) #indica quais são factor, num, int, etc
dados[1,4]#primeira linha quarta coluna
dados[,4]#quarta coluna
dados[c(10,6),]

homens <- dados[dados$Sex == "male",]
summary(homens)
table(homens$Survived)
barplot(table(homens$Survived))

mulheres <- dados[dados$Sex == "female",]
summary(mulheres)
table(mulheres$Survived)
barplot(table(mulheres$Survived))

sum(homens$Survived == 1)

pobre_homem <- homens[homens$Pclass == "3",]
summary(pobre_homem)

library(ggplot2)

ggplot(data=homens, aes(x=Pclass,fill=Survived))+geom_bar()
