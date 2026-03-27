library(rvest)
library(dplyr)
library(tidytext)
library(ggplot2)

url <- "https://www.bbc.com/portuguese/articles/cql3lwgl3ldo"

html <- read_html(url)
html

titulo <- html|>
  html_elements("h1")|>
  html_text2()
titulo

noticia <- html |>
  html_elements("p.bbc-hhl7in")|>
  html_text2()

noticia <- paste(noticia, collapse = " ")
noticia

artigos <- data.frame(titulo, noticia)

?unnest_tokens
#token = qualquer elemento do texto

artigos |>
  unnest_tokens(output = words, input = noticia) |>
  count(words) |>
  arrange (desc(n))
