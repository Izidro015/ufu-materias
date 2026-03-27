module Main (main) where


ex1a:: Bool->Bool->Bool
ex1a a b = (a||b) && not(a&&b)

ex1b:: Bool->Bool->Bool
ex1b a b = a /= b

ex1c:: Bool->Bool->Bool
ex1c a b = if a /= b then True else False

ex1d:: Bool->Bool->Bool
ex1d a b
  |a/=b = True
  |otherwise = False

ex2:: Int->Bool
ex2 x = if mod x 2 == 0 then True else False

ex3:: Int->Bool
ex3 x = if mod x 2 /= 0 then True else False

ex4maior:: Int->Int->Int 
ex4maior a b = if a>b then a else b

ex4menor:: Int->Int->Int 
ex4menor a b = if a<b then a else b

ex5:: Float->Float
ex5 d = pi*(r*r)
  where r = d/2

ex6:: Float->Float->Float->Int
ex6 a b c 
 |delta > 0 = 2
 |delta == 0 = 1
 |otherwise = 0
 where delta=b*b-4*a*c





--Lab 3
main::IO()
main = do  putStrLn "Digite uma palavra: "
           frase<-getLine
           if frase == reverse frase then putStrLn "A palavra eh um palindromo" else putStrLn "A palavra não eh um palindromo"
           mult
           temp
           situacao
           classeEleitoral




mult::IO()
mult = do putStrLn "Digite tres numeros float"
          num1 <- readLn::IO Float
          num2 <- readLn::IO Float
          num3 <- readLn::IO Float
          putStrLn("A multiplicacao eh: " ++ show (num1*num2*num3))

temp::IO()
temp = do putStrLn "Escreva uma temperatura em Fahrenheit"
          fah<-readLn::IO Float
          putStrLn "temperatura em Fahrenheit: "
          print (fah)
          putStrLn "temperatura em Celsius"
          let num = celsius(fah)
          print(num)
celsius::Float->Float
celsius fah = (5/9)*(fah-32)

situacao::IO()
situacao = do putStrLn"Digite traes notas: "
              nota1 <- readLn :: IO Float
              nota2 <- readLn :: IO Float
              nota3 <- readLn :: IO Float
              let media = (nota1+nota2+nota3)/3
              putStrLn("A media eh " ++ calcMedia media)
calcMedia::Float->String
calcMedia media
 |media<3 = "Reprovado"
 |media>7 = "Aprovado"
 |otherwise = "exame especial"

classeEleitoral::IO()
classeEleitoral = do putStrLn ">Classe eleitoral"
                     putStrLn ">--------------------------------"
                     putStrLn "Digite a idade da pessoa: "
                     idade <- readLn :: IO Int
                     putStrLn (calcIdade idade)
calcIdade::Int->String
calcIdade idade
 |idade<16 = "Não eleitor"
 |idade>=16 && idade<18 = "Eleitor facultativo"
 |idade>65 = "Eleitor facultativo"
 |idade>=18 && idade<=65 = "Eleitor obrigatorio"





--Lab 4
fatorialDuplo::Int->Int 
fatorialDuplo n
 |n == 0 = 1
 |n == 1 = 1
 |n > 0 = fatorialDuplo (n-2)*n

quoci::Int->Int->Int 
quoci numerador denominador
 |numerador == denominador = 1
 |numerador == 0 = 0
 |numerador>denominador = denominador + quoci(numerador-denominador*denominador)numerador
 |otherwise = 0
{-resto::Int->Int->Int 
resto denominador q
 |denominador<q = p
 |otherwise = resto(denominador-q)q-}





--Lab 5
--Ex 1

extraiPrimeiro:: [(a,b)]->[a]
extraiPrimeiro lista = map fst lista

maiusculas:: String -> String
maiusculas str = map toUpper str

dobros::Num a => [a] ->[a]
dobros lista = map (*2) lista

--Ex 2

pares:: [Int] -> [Int]
pares lista = filter even lista

alfa:: String -> String 
alfa str = filter isAlpha str

rm_char:: Char -> String -> String
rm_char c str = filter (/= 'c') str

--Ex 3

produto:: Num a=>[a] -> a
produto lista = foldr (*) 1 lista

e_logico:: [Bool]->Bool
e_logico lista = foldr (&&) True lista

concatena:: [String] -> String
concatena lista = foldr (++) "" lista





--Lab 6
{-  1) a- Válida, lista de caracteres
       b- Válida, tripla
       c- Válida, lista de tupla
       d- Válida, tupla de listas
       e- Inválida
    2) a- Retorna o segundo elemento da lista xs
       b- Retorna os elementos em uma tupla
       c- True quando xs é igual ao seu inverso (palindromo)
       -}
       
--Ex 3
ultimo::[Int]->Int
ultimo (h:t)
            |t == [] = h
            |otherwise = ultimo t 

ultimo2::[Int]->Int
ultimo2 [x] = x
ultimo2 (h:t) = ultimo2 t

ultimo3::[Int]->Int
ultimo3 (h:t) = if(t==[]) then h
                else ultimo3 t
                
--Ex 4
type Aluno = (Integer, [Char], Double)
type Curso = [Aluno]
getNota::Aluno->Double
getNota(_,_,nota) = nota
getNome::Aluno->[Char]
getNome(_,nome,_) = nome
--a)
maiorNota::Curso->[Char]
maiorNota [a] = getNome a
maiorNota (a1:a2:t)
 |getNota a1> getNota a2 = maiorNota (a1:t)
 |otherwise = maiorNota (a2:t)
--curso = [(1,"joao",10), (2,"maria",9), (3,"paulo",8)]

--b)
insereAluno::Aluno->Curso->Curso
insereAluno a [] = [a]
insereAluno a (h:t)
  |a==h = (h:t)
  |otherwise = h : insereAluno a t
--curso = [(1,"joao",10), (2,"maria",9)]
--insereAluno(3,"pedro",7) curso





--Lab 7
--Ex 1
--a) 
{-data Forma = Circulo Float | Retangulo Float Float
ehRedonda::Forma->Bool
ehRedonda (Circulo _) = True
ehRedonda _ = False
--b)
area_C :: Float -> Float
area_C r = pi * (r * r)
area_R:: Float -> Float -> Float
area_R b h = b * h
--c) O construtor é tipo Forma.-}
--d) 
data Forma = Circulo Float | Retangulo Float Float | Triangulo Float Float
ehRedonda::Forma->Bool
ehRedonda (Circulo _) = True
ehRedonda _ = False
area_C :: Float -> Float
area_C r = pi * (r * r)

area_R:: Float -> Float -> Float
area_R b h = b * h

area_T::Float -> Float -> Float
area_T b h = (b*h)/2

--Ex 2
{-a) Float, Float
copia a função, e pede :t dobro
b) Float, Bool
c) Float, Float, Double-}

--Ex 3
{-a)
copia a função, e pede :t [sum,length]-}

--Ex 4
type Coordenada = (Double,Double)
data Coord = Coord Double Double deriving (Show)
soma_coordenada:: Coordenada -> Coordenada -> Cordenada
soma_coordenada (x1,y1) (x2,y2) = (x1+x2, y1+y2)
soma_coordenada2::Coord -> Coord -> Coord
soma_coordenada2 (Coord x1 y1) (Coord x2 y2) = Coord (x1+x2) (y1+y2
{-sq::Int -> Int
sq x = foldr(+) 0 (map(^2)[1..x])

sqp::[Int]->Int
sqp x = foldr (+) 0 (map(^3)(filter even x))-}





--Lab 8
Import Data.char
--Ex 1
--a)
primeiros:: [(a,b)]->[a]
primeiros x = map(fst)x
--b)
maiscula:: String -> String
maiscula x = map(toUpper) x 
--c)
dobros:: Num a => [a] -> [a]
dobros a = map(*2) x
--Ex 2
--a)
pares:: [Int]->[Int]
pares x = filter even x
--b)
alfa:: String -> String
alfa x = filter isAlpha x 
--c) 
rm_char:: Char -> String -> String
rm_char x y = filter (\= 'a')srt 
--Ex 3 
--a)
produto:: Num a => [a] ->a
produto lista = foldr (*) 1 lista
--b)
e_logico::[Bool] -> Bool
e_logico x = foldr (&&) True x 
--c)
concatena::[String] -> String
concatena x = foldr (++) "" x 
