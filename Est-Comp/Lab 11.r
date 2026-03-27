library(rvest)
library(ggplot2)
library(dplyr)
library(stringr)

url <- "https://www.timeout.com/film/best-horror-films"
html <- read_html(url)

nomes <- html|>
  html_elements("h3._h3_cuogz_1")|>
  html_text2()

posicao <- str_extract_all(string = nomes, pattern = "^\\d+")
posicao <- unlist(posicao)
posicao

posicao <- as.numeric(posicao)
posicao

anos <- unlist(str_extract_all(string = nomes, pattern = "\\(\\d+\\)$"))
anos <- unlist(str_extract_all(string = anos,pattern =  "\\d+"))
anos


titulos <- str_remove_all(nomes, "^\\d+\\.\\s+")
titulos <- str_remove_all(titulos, "\\s+\\(\\d+\\)$")
titulos

filmes_horror <- data.frame (posicao, titulos, anos)
write.csv(filmes_horror, file = "filmes_horror.csv", row.names = FALSE)





################################################################################
#melhores filmes imdb 
url <- "https://www.bosshunting.com.au/entertainment/movies/best-movies-imdb/"
html <- read_html(url)

nomes2 <- html|>
  html_elements("ol.wp-block-list li")|>
  html_text2()
nomes2

posicao <- str_extract_all(string  = nomes2, pattern = "^\\d+")
posicao <- unlist(posicao)
posicao
