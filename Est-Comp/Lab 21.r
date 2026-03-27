install.packages("jpeg")

library(jpeg)
library(ggplot2)

gatinho <- readJPEG("francis.jpg") # coloca sua imagem aqui
str(gatinho)

R <- as.vector(gatinho[,,1]) # red
G <- as.vector(gatinho[,,2]) # green
B <- as.vector(gatinho[,,3]) # blue

x <- rep(1:809, each = 1200)
x

y <- rep(1200:1, times = 809)
y

dados <- data.frame(x, y, R, G, B)
head(dados)

?kmeans

clusterizacao <- kmeans(x = dados[,3:5], centers = 3, nstart = 20)
clusterizacao

clusterizacao$centers

cores <- rgb(clusterizacao$centers)
cluster <- as.factor(clusterizacao$centers)

dados$cluster <- cluster
head(dados)

ggplot(data = dados, aes(x = x, y = y, col = cluster)) +
  geom_point() +
  scale_color_manual(values = cores) +
  theme_void()
