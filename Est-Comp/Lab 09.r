library(randomForest)
library(ggplot2)
library(rpart)
library(rpart.plot)

cancer <- read.csv(file = "cancer.csv", header = TRUE)
str(cancer)
cancer$diagnosis <- as.factor(cancer$diagnosis)
n <- round(0.8*nrow(cancer))


set.seed(2145)
indices_treino <- sample(1:nrow(cancer), size = n, replace = FALSE)

treino <- cancer[indices_treino,]
teste <- cancer[-indices_treino,]

modelo.arvore <- rpart(formula = diagnosis~ ., data = treino, method = "class")
rpart.plot(modelo.arvore, extra = 101)

previsao <- predict(modelo.arvore, newdata = teste, type = "class")

mean(previsao == teste$diagnosis)

floresta <- randomForest(formula = diagnosis ~ ., data = treino, ntree = 200)
floresta


previsao.floresta <- predict(floresta, newdata = teste, type = "class")
mean(previsao.floresta == teste$diagnosis)

=============================================================================================================
library(rvest)
library(ggplot2)
library(dplyr)

url <- "https://pt.wikipedia.org/wiki/Lista_de_unidades_federativas_do_Brasil_por_alfabetiza%C3%A7%C3%A3o"

html <- read_html(url)

html_elements(html, "h1")
html_text2(html_elements(html,"h1"))

html |> 
  html_elements("h1")|>
  html_text2()

html |>
  html_elements("table")|>
  html_table()

tabelas <- html|>
  html_elements("table")|>
  html_table()

taxa <- tabelas[[3]]
