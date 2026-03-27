library(httr)
library(dplyr)
library(ggplot2)
library(jsonlite)
#BLAZE
url <- "https://ads.mythad.com/log/common/co/api"
url <- "https://blaze1.space/api/roulette_games/history?startDate=2024-08-14T16:43:39.175Z&endDate=2024-09-13T16:43:39.176Z&page=1"


GET(url)#pede pra entrar no site
dados <- content(GET(url), "text")
dados
dados <- fromJSON(dados)#arruma os dados para um jeito entendível
table(dados$records$color)#cria tabela de frequencia de cores

resutlados <- c()
url_base <- "https://blaze1.space/api/roulette_games/history?startDate=2024-08-14T16:43:39.175Z&endDate=2024-09-13T16:43:39.176Z&page"
for(j in 1:50){
  url <- paste0(url_base, j)
  dados <- content(GET(url),"text")
  dados <- fromJSON(dados)
  resultados <- c(resultados, dados$records$color)
}
resultados
prop.table(table(resultados))
################################################################################

#Música
library(rvest)
library(dplyr)
library(tidytext)
library(ggplot2)

url <- "https://www.letras.mus.br/paul-mccartney/89715/"

html <- read_html(url)
html|>  
  html_elements("h1")|>
  html_text2()

letra <- html|>
  html_elements("div.lyric")|>
  html_elements("p")|>
  html_text2()|>
  paste(collapse = " ")
letra

#tranforma letracomlixo em letrabonita
letra <- data.frame(letra)
letra |>
  unnest_tokens(output = word, input = letra)|>#faça tokens?
  count(word, sort = TRUE)|>
  head(n = 10)|>
  ggplot(aes(y = word, x = n))+
  geom_col()
