import Data.List (find)

type IdentificaçãoEstudante = Int
type PrimeiroNome = String
type Sobrenome = String
type Idade = Int

data Estudante = Estudante { identificaçãoEstudante :: IdentificaçãoEstudante
                            , primeiroNome :: PrimeiroNome
                            , sobrenome :: Sobrenome
                            , idade :: Idade
                            }

instance Show Estudante where
    show (Estudante id primeiro ultimo idade) = "Estudante { ID: " ++ show id ++
                                                ", Primeiro Nome: " ++ primeiro ++
                                                ", Sobrenome: " ++ ultimo ++
                                                ", Idade: " ++ show idade ++ " }"

baseDeDadosInicial :: [Estudante]
baseDeDadosInicial = []

adicionarEstudante :: IdentificaçãoEstudante -> PrimeiroNome -> Sobrenome -> Idade -> [Estudante] -> [Estudante]
adicionarEstudante id primeiro sobrenome idade baseDeDados = baseDeDados ++ [Estudante id primeiro sobrenome idade]

encontrarEstudantePorId :: IdentificaçãoEstudante -> [Estudante] -> Maybe Estudante
encontrarEstudantePorId id = find (\estudante -> identificaçãoEstudante estudante == id)

atualizarEstudante :: IdentificaçãoEstudante -> Estudante -> [Estudante] -> [Estudante]
atualizarEstudante id novoEstudante = map (\estudante -> if identificaçãoEstudante estudante == id then novoEstudante else estudante)

menu :: [Estudante] -> IO ()
menu baseDeDados = do
    putStrLn "Escolha uma opção:"
    putStrLn "1. Adicionar estudante"
    putStrLn "2. Recuperar estudante por ID"
    putStrLn "3. Atualizar informações do estudante"
    putStrLn "4. Sair"
    opção <- getLine
    case opção of
        "1" -> do
            putStrLn "Digite a identificação do estudante:"
            id <- readLn
            putStrLn "Digite o primeiro nome do estudante:"
            primeiro <- getLine
            putStrLn "Digite o sobrenome do estudante:"
            ultimo <- getLine
            putStrLn "Digite a idade do estudante:"
            idade <- readLn
            let novaBaseDeDados = adicionarEstudante id primeiro ultimo idade baseDeDados
            putStrLn "Estudante adicionado:"
            print novaBaseDeDados
            menu novaBaseDeDados
        "2" -> do
            putStrLn "Digite a identificação do estudante:"
            id <- readLn
            case encontrarEstudantePorId id baseDeDados of
                Just estudante -> do
                    putStrLn "Estudante encontrado:"
                    print estudante
                    menu baseDeDados
                Nothing -> do
                    putStrLn "Estudante não encontrado."
                    menu baseDeDados
        "3" -> do
            putStrLn "Digite a identificação do estudante para atualizar:"
            id <- readLn
            putStrLn "Digite o novo primeiro nome do estudante:"
            primeiro <- getLine
            putStrLn "Digite o novo sobrenome do estudante:"
            ultimo <- getLine
            putStrLn "Digite a nova idade do estudante:"
            idade <- readLn
            case encontrarEstudantePorId id baseDeDados of
                Just _ -> do
                    let estudanteAtualizado = Estudante id primeiro ultimo idade
                        novaBaseDeDados = atualizarEstudante id estudanteAtualizado baseDeDados
                    putStrLn "Informações do estudante atualizadas:"
                    print novaBaseDeDados
                    menu novaBaseDeDados
                Nothing -> do
                    putStrLn "Estudante não encontrado."
                    menu baseDeDados
        "4" -> putStrLn "Encerrando o programa..."
        _ -> do
            putStrLn "Opção inválida."
            menu baseDeDados

main :: IO ()
main = do
    putStrLn "Bem-vindo ao sistema de gerenciamento de estudantes!"
    menu baseDeDadosInicial
