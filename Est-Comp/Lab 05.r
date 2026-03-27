iris
library(ggplot2)
#passo 1: dividir em treino e teste

set.seed(1711)#deixa o embaralhamento na mesma ordem
iris <- iris[sample(nrow(iris)),] #embaralha a ordem
n <- round(0.8 *nrow(iris))#pega 80% dos 150 da iris
n 
treinamento <- iris[1:n,]#pega da primeira até a nlinha de iris
teste <- iris[-(1:n),]#pega o que n não pegou

ggplot(data = treinamento, aes(x = Species))+
  geom_bar()

ggplot(data = treinamento, aes(x = Petal.Length))+
  geom_histogram(bins=20, fill = "purple")
 
summary(treinamento$Petal.Length)

ggplot(data = treinamento, aes(y = Petal.Length))+
  geom_boxplot(fill = "purple")+
  facet_wrap(~Species)
#a setosa sempre tera um valor menor que qualquer outra petala

ggplot(data = treinamento, aes(y = Petal.Width))+
  geom_boxplot(fill = "purple")+
  facet_wrap(~Species)
#largura das petalas, a setosa tem a menor largura entre todas

ggplot(data = treinamento, aes(y = Sepal.Length))+
  geom_boxplot(fill = "purple")+
  facet_wrap(~Species)
#

ggplot(data = treinamento, aes(y = Sepal.Width))+
  geom_boxplot(fill = "purple")+
  facet_wrap(~Species)
 
ggplot(data = treinamento, aes(x = Petal.Length, y = Petal.Width, col = Species))+
  geom_point(size = 1)+
  theme_classic()



resultados<- c()
for(j in 1:nrow(teste)){
  if(teste$Petal.Length[j]<2.5){
    resultados[j]<-"setosa"
  }else{
    if(teste$Petal.Width[j]<1.75){
      resultados[j]<-"versicolor"
    }else{
      resultados[j]<-"virginica"
    }
  }
}
teste$Species == resultados
mean(teste$Species == resultados)
