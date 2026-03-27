module Main (main) where
import System.IO (stdout, hSetBuffering, BufferMode(NoBuffering))
import System.Random

main :: IO ()
main = do
          hSetBuffering stdout NoBuffering
          putStrLn "Bem-vindo ao Jogo de Adivinhação!"
          putStrLn "Estou pensando em um número entre 1 e 100. Tente adivinhar.\n\n"
          numAleatorio <- randomRIO (1, 100) :: IO Int
          aposta 1 numAleatorio

aposta :: Int -> Int -> IO ()
aposta n numAleatorio = do
                            putStrLn ("Tentativa " ++ show n)
                            putStr "Digite seu palpite: "
                            palpite <- readLn :: IO Int
                            if palpite < numAleatorio 
                               then do putStrLn ("Seu palpite de " ++ show palpite ++ " está abaixo do número correto.")
                                       aposta (n + 1) numAleatorio
                            else if palpite > numAleatorio then do putStrLn ("Seu palpite de " ++ show palpite ++ " está acima do correto.")
                                                                   aposta (n + 1) numAleatorio
                                 else do putStrLn ("Seu palpite de " ++ show palpite ++ " está correto!\nParabéns! Você acertou em " ++ show n ++ " tentativas.")
                                         conteudo <- readFile "highscore.txt"
                                         let record = read conteudo :: Int
                                         if n < record then do putStrLn ("Parabéns! Você bateu o recorde.")
                                                               writeFile "highscore.txt" (show n)
                                         else putStr ("\n")
                                         putStr ("Digite s para jogar novamente ou qualquer coisa para sair: ")
                                         op <- getLine
                                         jogar_novamente op        



jogar_novamente :: String -> IO()
jogar_novamente op = if op == "s" then do numAleatorio <- randomRIO (1, 100) :: IO Int
                                          putStrLn ("Estou pensando em um número entre 1 e 100. Tente adivinhar.\n\n")
                                          aposta 1 numAleatorio 
                     else putStrLn ("Obrigado por jogar o Jogo de Adivinhação!")
                                                                
