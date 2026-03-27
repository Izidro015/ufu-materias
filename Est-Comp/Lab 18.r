grilo <- read.csv(file = "grilo.txt", TRUE)
ggplot(data = grilo, aes(x = temperatura, y = frequencia))+
  geom_point()

correlacao <- cor(grilo$temperatura, grilo$frequencia)
correlacao <- cor(grilo)

ggplot(data = grilo, aes(x = frequencia))+
  geom_histogram(bins = 10)

ggplot(data = grilo, aes(x = temperatura, y = frequencia))+
  geom_point()+
  theme_minimal()+
  geom_smooth(method = "lm")#reta de regressão linear simples

modelo_linear <- lm(formula = frequencia ~ temperatura, data = grilo)
modelo_linear
summary (grilo$temperatura)

w <- data.frame(temperatura = c(21, 23.6, 30.9))
predict(modelo_linear, newdata = w)
#================^ grilo ^================V pinguins V================
library(palmerpenguins)
library(dplyr)
pinguins <- na.omit(penguins)
cor(pinguins$bill_length_mm, pinguins$bill_depth_mm)

names(pinguins)
cor(pinguins[,3:6])

ggplot(data = pinguins, aes(x = flipper_length_mm, y = body_mass_g, color = species))+
  geom_point()+
  theme_minimal()+
  geom_smooth(method = 'lm')

pinguins|>
  filter(species == "Chinstrap")|>
  select(flipper_length_mm, body_mass_g)|>
  cor()

modelo2 <- lm(formula = flipper_length_mm ~ body_mass_g + bill_length_mm, data = pinguins)
modelo2
summary(modelo2)#fica estranho msm
