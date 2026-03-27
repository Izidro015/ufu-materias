---
title: "Tutorial para classificar pinguins"
author: "Izidro"
lang: "pt"
date: 2024-08-23
format: html
editor: visual
---

## Objetivos desse tutorial

O objetivo desse tutorial é criar um modelo de classificação que seja capaz de prever a espécie de um pinguim a partir de seu peso, tamanho da asa, tamanho do bico e profundidade do bico. Para isso, construiremos do zero o modelo KNN.

## Lendo conjunto

Vamo iniciar nosso trabalho lendo o pacote 'palmerpenguins' e salvando o conjunto em um objeto chamado 'pinguins'.
```{r}
library(palmerpenguins)#lendo o pacote
set.seed(1443)
pinguins <- penguins
str(pinguins)
```

A seguir vamos imprimir um resumo estatístico dos dados de cada uma das variáveis dos dados.

```{r}
summary(pinguins)
```

A partir do reusmo das variáveis, identificamos alguns valores faltantes. Vamos removê-los.

```{r}
pinguins <- na.omit(pinguins)
summary(pinguins)
```

## Dividindo o treino em teste

```{r}
pinguins <- pinguins[sample(nrow(pinguins)),]
n <- round(0.8 *nrow(pinguins))

treinamento <- pinguins[1:n,]
summary(treinamento)
teste <- pinguins[-(1:n),]
summary(teste)
```

## Visualização de dados

Vamos identificar padrões no conjunto de treinamento para construirmos nosso modelo.

```{r}
library(ggplot2)


ggplot(data = treinamento, aes(x = species, y = flipper_length_mm))+
  geom_boxplot()


ggplot(data = treinamento, aes(x = body_mass_g, y = bill_length_mm, color = species))+
  geom_point()+
  theme_minimal()
```

## Classificando o primerio pinguim do teste

```{r}
distancias <- c()
for(k in 1:nrow(treinamento)){
  distancias[k] <- sqrt((teste$body_mass_g[1] - treinamento$body_mass_g[k])**2 + (teste$bill_length_mm[1] - treinamento$bill_length_mm[k])**2)
}
distancias
treinamento$species[order(distancias)[1]]
teste$species[1]
```

```{r}
classificacao <- c()
for(j in 1:nrow(teste)){
  distancias <- c()
  for(k in 1:nrow(treinamento)){
    distancias[k] <- sqrt((teste$body_mass_g[j] - treinamento$body_mass_g[k])**2 + (teste$bill_length_mm[j] - treinamento$bill_length_mm[k])**2)
  }
  
  classificacao[j] <- as.character(treinamento$species[order(distancias)[1]])
}
mean(classificacao == teste$species)
```
