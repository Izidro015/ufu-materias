library(tidytext) #manipula texto
library(dplyr) #manipula dados
library(ggplot2)
library(tidyr)#organizar um conjunto bagunçado
library(stopwords)
library(rvest)#raspagem de dados

url <- "https://www.bbc.com/portuguese/articles/cpw5105nqleo"

html <- read_html(url)
texto <- html|>
  html_elements("p.bbc-hhl7in")|>
  html_text()|>
  paste(collapse = " ")

texto <- paste(texto, collapse = " ")
#para conectar tudo em um unico dataframe,para a cada linha, termos um parágrafo

conjunto <- data.frame(texto)
conjunto
#separa os fragmentos do texto que chamamos de tokens

conjunto|>
  unnest_tokens(output = word, input = texto)|>
  count(word, sort = TRUE)|>
  top_n(10)


#stopwords("pt")
stopwords_br <- data.frame(word = stopwords("pt"))
conjunto|>
  unnest_tokens(output = word, input = texto)|>
  anti_join(stopwords_br)|>
  count(word, sort = TRUE)|>
  top_n(10)

conjunto|>
  unnest_tokens(output = word, input = texto)|>
  anti_join(stopwords_br)|>
  count(word, sort = TRUE)|>
  top_n(10)|>
  mutate(word = reorder(word,n))|>
  ggplot(aes(x = n, y = word))+
  geom_col(color = "gray", fill = "purple")+
  theme_minimal()

library(janeaustenr)
livro <- prideprejudice
pride <- data.frame(texto=livro)
stopwords_en <- data.frame(word = stopwords("en"))

pride |>
  unnest_tokens(output = word, input = livro)|>
  anti_join(stopwords_en)|>
  count(word, sort = TRUE)|>
  top_n(10)|>
  mutate(word = reorder(word,n))|>
  ggplot(aes(x = n, y = word))+
  geom_col(color = "purple", fill = "orangered4")+
  theme_minimal()


sentimentos <- get_sentiments("bing")
library(stringr)
capitulos <- str_detect(pride$texto, "^Chapter \\d+")
capitulos <- cumsum(capitulos)
library(tidyr)

pride|>
  mutate(capitulo = capitulos)|>
  unnest_tokens(word, texto)|>
  inner_join(sentimentos)|>
  count(capitulo, sentiment)|>
  spread(sentiment, n, fill = 0)|>
  mutate(total = positive - negative)|>
  ggplot(aes(x = capitulo, y = total))+
  geom_col()+
  theme_minimal()
