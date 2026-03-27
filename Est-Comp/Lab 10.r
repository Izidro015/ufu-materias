library(rvest)
library(dplyr)
library(ggplot2)

#url <- "https://pt.wikipedia.org/wiki/Lista_de_unidades_federativas_do_Brasil_por_taxa_de_homic%C3%ADdios"
#html <- read_html(url)
#html 

#html_elements(html, "table")
#tabelas <- html|>
  #html_elements("table")|>
  #html_table()

#homicidios <- tabelas[[1]]
 






url <- "https://pt.wikipedia.org/wiki/Lista_de_unidades_federativas_do_Brasil_por_alfabetiza%C3%A7%C3%A3o"

html <- read_html(url)

tabelas <- html|>
  html_elements("table")|>
  html_table()

taxa <- tabelas[[3]]
alfabetizacao <- alfabetizacao[,c(2,3)]
names(alfabetizacao) <- c("estado", "taxa")
names(alfabetizacao)
library(stringr)


str_replace_all(string = "pedro145", pattern = "\\d", replacement = "")
part1 <- str_replace_all(string = alfabetizacao$taxa, pattern = ",", replacement = ".")

parte2 <- str_replace_all(string = part1, pattern = "%", replacement = "")
parte_final <- as.numeric(parte2)
parte_final
parte_final<- parte_final/100

alfabetizacao$taxa <- parte_final
library(geobr)

minas <- read_state(code_state = "MG")
ggplot(data = minas)+
  geom_sf(fill = "orange")+
  theme_void()
municipiomg <- read_municipality(code_muni = "MG")
ggplot(data = municipiomg)+
  geom_sf()+
  theme_void()
estados <- read_state()
estados$name_state
order(estados$name_state)
estados[2,]
estados <- estados[order(estados$name_state),]
estados
alfabetizacao <- alfabetizacao[order(alfabetizacao$estado),]
alfabetizacao

estados$taxa <- alfabetizacao$taxa

ggplot(data = estados, aes(fill = taxa))+
  geom_sf()+
  scale_fill_gradient(high = "#132B43",
                      low = "#56B1F7")
