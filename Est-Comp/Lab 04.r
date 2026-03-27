install.packages("ggplot2")
library(ggplot2)
titanic <- read.table(file = "titanic.txt", sep = ",", header = TRUE)
titanic <- titanic[,-c(1,9:12)]#tira a primeira linha e as colunas 9,10,11,12
str(titanic)

titanic$Survived <- as.factor(titanic$Survived)
titanic$Pclass <- as.factor(titanic$Pclass)
titanic$Sex <- as.factor(titanic$Sex)
str(titanic)
summary(titanic)#da um resumo mais bonito

ggplot(data = titanic, aes(x = Survived, fill = Sex))+
  geom_bar()+#geom_bar(color = "#2E073F",fill = "pink")+
  scale_fill_manual(values = c("male" = "green",female = "pink"))
  theme_minimal()
#aes(x = Survived) = oq vai aparecer no eixo x

ggplot(data = titanic, aes(x = Sex, fill = Survived))+#melhor pra comparar
  geom_bar()+#geom_bar(color = "#2E073F",fill = "pink")+
  scale_fill_manual(values = c("0" = "green", "1" = "pink"))
  theme_minimal()
  #aes(x = Survived) = oq vai aparecer no eixo x
  
ggplot(data = titanic, aes(x = Sex, fill = Survived))+
  geom_bar()+#geom_bar(color = "#2E073F",fill = "pink")+
  labs(title = "JANELA DE INVERNO DO GIGANTE DA COLINA (1912)", x = "Sexo", y = "Quantidade", fill = "Sobreviveu")+
  scale_fill_manual(values = c("0" = "purple", "1" = "pink"), 
                    labels = c("0"= "VASCO DA GAMA", "1" = "TA VIVO"))+
  facet_wrap(~Pclass)+
  scale_x_discrete(labels = c("female" = "mulher", "male" = "homem"))
  theme_classic()
=============================================================================================
