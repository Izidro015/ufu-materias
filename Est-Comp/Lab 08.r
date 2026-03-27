library(class)
library(ggplot2)
library(rpart)
library(rpart.plot)

n <- round(0.8*nrow(cancer))

indices_treino <- sample(1:nrow(cancer), size = n, replace = FALSE)

treino <- cancer[indices_treino,]
teste <- cancer[-indices_treino,]

modelo.arvore <- rpart(formula = diagnosis~ ., data = treino, method = "class")
rpart.plot(modelo.arvore, extra = 101)

previsao <- predict(modelo.arvore, newdata = teste, type = "class")

mean(previsao == teste$diagnosis)
