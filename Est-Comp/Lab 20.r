populacao <- sample(0:1,size = 100000, replace = TRUE,prob = c(0.9,0.1))
valor_real <- mean(populacao)

amostra <- sample(populacao, size = 200, replace = TRUE)
media <- mean(amostra)


prop <- prop.test(sum(amostra == 1), 200, p = 0.1, alternative = "two.sided")

library(Stat2Data)
library(ggplot2)
data("Oysters")
ggplot(Oysters, aes(x = TwoD, y = Volume))+
  geom_point()+
  geom_smooth(method = "lm")
correlacao <- cor(Oysters$TwoD, Oysters$Volume)

modelo1 <- lm(data = Oysters, formula = Volume ~ TwoD)

summary(modelo1)
modelo1$residuals
