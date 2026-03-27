read.csv("noticias")
#calcular usando o teorema de Bayes

library(dplyr)
library(tidytext)
library(SnowballC)#lematizaçção
library(quanteda)#analise qunatitativa do texto
library(quanteda.textmodels)#modelagem de texto

stopwords_pt <- data.frame(word = stopwords("pt"))

noticias[1,]|>
  unnest_tokens(word, texto)|>
  anti_join(stopwords_pt)|>
  count(word, sort = TRUE)|>
  top_n(20)

noticias[1,]|>
  unnest_tokens(word, texto)|>
  anti_join(stopwords_pt)|>
  mutate(word = wordStem(word, "portuguese"))|>
  count(word, sort = TRUE)|>
  top_n(20)

noticias_tokens <- tokens(noticias$texto, remove_punct = TRUE, remove_symbols = TRUE, remove_numbers = TRUE, remove_url = TRUE)|>
  tokens_remove(stopwords("portuguese"))|>
  tokens_wordstem(language = "portuguese")

matriz_frequencia <- dfm(noticias_tokens)

n <- round(0.8*nrow(noticias))
n
indices <- sample(1:nrow(noticias),size = n, replace = FALSE)

treino <- matriz_frequencia[indices,]
teste <- matriz_frequencia[-indices,]


modelo_nb <- textmodel_nb(treino, noticias$categorias[indices])#classifica teorema com base no teorema de bayes

previsao <- predict(modelo_nb, newdata = teste)

mean(previsao == noticias$categorias[-indices])


url <- "https://www.bbc.com/portuguese/topics/cvjp2jr0k9rt"
html <- read_html(url)
#html|>
  #html_elements("")

#Fazer a msm parada para toda dnovo, só q com todas as noticias de economia da bbc
