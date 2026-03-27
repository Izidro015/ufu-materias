data(iris)

library(ggplot2)

ggplot(data = iris, aes(x= Petal.Length, y = Petal.Width))+
  geom_point()

cor(iris$Petal.Length, iris$Petal.Width)
cor(iris[,-5])

setosa <- iris[iris$Species == "setosa",]
cor(setosa$Petal.Length, setosa$Petal.Width)

femur <- read.csv(file = "femur.csv", head = TRUE)
str(femur)
femur <- femur[,-1]
masc <- femur[femur$genero == "Male",]
fem <- femur[femur$genero == "Female",]

cor(masc$altura, masc$femur)

cor(fem$altura, fem$femur)

ggplot(data = masc, aes(x = femur, y = altura))+
  geom_point()

modelo_linear <- lm(data = masc, formula = altura ~ femur)
modelo_linear

summary(masc$femur)
