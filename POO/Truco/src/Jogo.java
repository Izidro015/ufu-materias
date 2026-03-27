import java.io.*;
import java.util.*;

public class Jogo {
    private List<Jogador> jogadores;
    private List<Dupla> duplas;
    private Baralho baralho;
    private Scanner scanner;

    private Dupla dupla1, dupla2;
    private int valorMao;
    private boolean trucoAtivo;
    private Dupla ultimaATrucar;
    private boolean jogoAtivo;
    private List<Jogador> ordemJogadores;
    private int indiceProximoJogador;

    private static final String ARQUIVO_JOGADORES = "jogadores.txt";
    private static final String ARQUIVO_DUPLAS = "duplas.txt";
    private static final String ARQUIVO_ESTATISTICAS = "estatisticas.txt";

    public Jogo() {
        this.jogadores = new ArrayList<>();
        this.duplas = new ArrayList<>();
        this.baralho = new Baralho();
        this.scanner = new Scanner(System.in);
        this.jogoAtivo = true;
        this.ordemJogadores = new ArrayList<>();
        this.indiceProximoJogador = 0;

        carregarDados();
    }

    public void executarMenu() {
        while (jogoAtivo) {
            mostrarMenu();
            try {
                int opcao = Integer.parseInt(scanner.nextLine());
                processarOpcao(opcao);
            } catch (NumberFormatException e) {
                System.out.println("Opção inválida! Digite um número.");
            } catch (Exception e) {
                System.err.println("Erro: " + e.getMessage());
            }
        }
    }

    private void mostrarMenu() {
        System.out.println("\n=== JOGO DE TRUCO ===");
        System.out.println("1. Cadastrar Jogador");
        System.out.println("2. Listar Jogadores");
        System.out.println("3. Cadastrar Dupla");
        System.out.println("4. Listar Duplas");
        System.out.println("5. Iniciar Jogo");
        System.out.println("6. Ver Estatísticas");
        System.out.println("7. Salvar Dados");
        System.out.println("8. Sair");
        System.out.print("Escolha uma opção: ");
    }

    private void processarOpcao(int opcao) throws IOException {
        switch (opcao) {
            case 1:
                cadastrarJogador();
                break;
            case 2:
                listarJogadores();
                break;
            case 3:
                cadastrarDupla();
                break;
            case 4:
                listarDuplas();
                break;
            case 5:
                iniciarJogo();
                break;
            case 6:
                verEstatisticas();
                break;
            case 7:
                salvarDados();
                break;
            case 8:
                salvarDados();
                jogoAtivo = false;
                System.out.println("Obrigado por jogar!");
                break;
            default:
                System.out.println("Opção inválida!");
        }
    }

    private void cadastrarJogador() {
        if (jogadores.size() >= 4) {
            System.out.println("Já existem 4 jogadores cadastrados!");
            return;
        }

        System.out.print("Nome do jogador: ");
        String nome = scanner.nextLine();

        for (Jogador j : jogadores) {
            if (j.getNome().equalsIgnoreCase(nome)) {
                System.out.println("Jogador já existe!");
                return;
            }
        }

        jogadores.add(new JogadorHumano(nome, jogadores.size() + 1));
        System.out.println("Jogador cadastrado com sucesso!");
    }

    private void listarJogadores() {
        if (jogadores.isEmpty()) {
            System.out.println("Nenhum jogador cadastrado.");
            return;
        }

        System.out.println("\n=== JOGADORES CADASTRADOS ===");
        for (int i = 0; i < jogadores.size(); i++) {
            Jogador j = jogadores.get(i);
            System.out.println((i + 1) + ". " + j.getNome());
        }
    }

    private boolean jogadorJaEstaEmDupla(Jogador jogador) {
        for (Dupla dupla : duplas) {
            if (dupla.getJogador1().equals(jogador) || dupla.getJogador2().equals(jogador)) {
                return true;
            }
        }
        return false;
    }

    private Dupla encontrarDuplaDoJogador(Jogador jogador) {
        for (Dupla dupla : duplas) {
            if (dupla.getJogador1().equals(jogador) || dupla.getJogador2().equals(jogador)) {
                return dupla;
            }
        }
        return null;
    }

    private void listarJogadoresDisponiveis() {
        System.out.println("\n=== Jogadores Disponíveis ===");
        int contador = 1;
        for (int i = 0; i < jogadores.size(); i++) {
            Jogador jogador = jogadores.get(i);
            if (!jogadorJaEstaEmDupla(jogador)) {
                System.out.printf("%d. %s\n", contador, jogador.getNome());
                contador++;
            }
        }

        if (contador == 1) {
            System.out.println("Nenhum jogador disponível.");
        }
    }

    private Jogador obterJogadorDisponivelPorIndice(int indiceEscolhido) {
        int contador = 1;
        for (Jogador jogador : jogadores) {
            if (!jogadorJaEstaEmDupla(jogador)) {
                if (contador == indiceEscolhido) {
                    return jogador;
                }
                contador++;
            }
        }
        return null;
    }

    private void cadastrarDupla() {
        if (jogadores.size() < 2) {
            System.out.println("É necessário pelo menos 2 jogadores para formar uma dupla!");
            return;
        }

        int jogadoresDisponiveis = 0;
        for (Jogador jogador : jogadores) {
            if (!jogadorJaEstaEmDupla(jogador)) {
                jogadoresDisponiveis++;
            }
        }

        if (jogadoresDisponiveis < 2) {
            System.out.println("É necessário pelo menos 2 jogadores disponíveis para formar uma dupla!");
            System.out.println("Jogadores disponíveis: " + jogadoresDisponiveis);
            return;
        }

        System.out.print("Nome da dupla: ");
        String nome = scanner.nextLine().trim();

        if (nome.isEmpty()) {
            System.out.println("Nome da dupla não pode estar vazio!");
            return;
        }

        for (Dupla d : duplas) {
            if (d.getNome().equalsIgnoreCase(nome)) {
                System.out.println("Dupla já existe!");
                return;
            }
        }

        listarJogadoresDisponiveis();

        try {//try e catch de verificação da dupla
            System.out.print("Escolha o primeiro jogador: ");
            int idx1 = Integer.parseInt(scanner.nextLine());

            Jogador jogador1 = obterJogadorDisponivelPorIndice(idx1);
            if (jogador1 == null) {
                System.out.println("Índice inválido para o primeiro jogador!");
                return;
            }

            System.out.print("Escolha o segundo jogador: ");
            int idx2 = Integer.parseInt(scanner.nextLine());

            Jogador jogador2 = obterJogadorDisponivelPorIndice(idx2);
            if (jogador2 == null) {
                System.out.println("Índice inválido para o segundo jogador!");
                return;
            }

            if (jogador1.equals(jogador2)) {
                System.out.println("Não é possível formar dupla com o mesmo jogador!");
                return;
            }

            if (jogadorJaEstaEmDupla(jogador1)) {
                Dupla duplaExistente = encontrarDuplaDoJogador(jogador1);
                System.out.printf("O jogador %s já está na dupla: %s\n",
                        jogador1.getNome(), duplaExistente.getNome());
                return;
            }

            if (jogadorJaEstaEmDupla(jogador2)) {
                Dupla duplaExistente = encontrarDuplaDoJogador(jogador2);
                System.out.printf("O jogador %s já está na dupla: %s\n",
                        jogador2.getNome(), duplaExistente.getNome());
                return;
            }

            Dupla dupla = new Dupla(nome, jogador1, jogador2, duplas.size() + 1);
            duplas.add(dupla);
            System.out.printf("Dupla '%s' cadastrada com sucesso!\n", nome);
            System.out.printf("Jogadores: %s e %s\n", jogador1.getNome(), jogador2.getNome());

        } catch (NumberFormatException e) {
            System.out.println("Por favor, digite apenas números válidos!");
        }
    }

    private void listarDuplas() {
        if (duplas.isEmpty()) {
            System.out.println("Nenhuma dupla cadastrada.");
            return;
        }

        System.out.println("\n=== DUPLAS CADASTRADAS ===");
        for (int i = 0; i < duplas.size(); i++) {
            System.out.println((i + 1) + ". " + duplas.get(i).toStringDetalhado());
            System.out.println();
        }
    }

    private void iniciarJogo() {
        if (duplas.size() < 2) {
            System.out.println("É necessário pelo menos 2 duplas para iniciar o jogo!");
            return;
        }

        selecionarDuplas();
        jogarQueda();
    }

    private void selecionarDuplas() {
        System.out.println("\n=== SELEÇÃO DE DUPLAS ===");
        listarDuplas();

        System.out.print("Escolha a primeira dupla: ");
        int idx1 = Integer.parseInt(scanner.nextLine()) - 1;

        System.out.print("Escolha a segunda dupla: ");
        int idx2 = Integer.parseInt(scanner.nextLine()) - 1;

        if (idx1 < 0 || idx1 >= duplas.size() || idx2 < 0 || idx2 >= duplas.size() || idx1 == idx2) {
            System.out.println("Seleção inválida!");
            return;
        }

        dupla1 = duplas.get(idx1);
        dupla2 = duplas.get(idx2);

        ordemJogadores.clear();
        ordemJogadores.add(dupla1.getJogador1());
        ordemJogadores.add(dupla2.getJogador1());
        ordemJogadores.add(dupla1.getJogador2());
        ordemJogadores.add(dupla2.getJogador2());
        indiceProximoJogador = 0;

        System.out.println("Duplas selecionadas:");
        System.out.println("Dupla 1: " + dupla1.getNome());
        System.out.println("Dupla 2: " + dupla2.getNome());
    }

    private void jogarQueda() {
        System.out.println("\n=== INICIANDO QUEDA ===");

        dupla1.setJogosGanhos(0);
        dupla1.setPontos(0);
        dupla2.setJogosGanhos(0);
        dupla2.setPontos(0);

        while (!dupla1.ganhouQueda() && !dupla2.ganhouQueda()) {
            jogarJogo();
            mostrarPlacar();
        }

        Dupla vencedora = dupla1.ganhouQueda() ? dupla1 : dupla2;
        Dupla perdedora = vencedora == dupla1 ? dupla2 : dupla1;

        System.out.println("\n" + vencedora.getNome() + " GANHOU A QUEDA!");

        vencedora.ganharQueda();
        perdedora.perderQueda();

        try {
            salvarEstatisticas();
        } catch (IOException e) {
            System.err.println("Erro ao salvar estatísticas: " + e.getMessage());
        }
    }

    private void jogarJogo() {
        System.out.println("\n=== NOVO JOGO ===");

        while (!dupla1.ganhouJogo() && !dupla2.ganhouJogo()) {//verifica se a queda terminou
            jogarMao();
        }

        Dupla vencedora = dupla1.ganhouJogo() ? dupla1 : dupla2;
        vencedora.ganharJogo();

        System.out.println(vencedora.getNome() + " ganhou o jogo!");
    }

    private void jogarMao() {
        valorMao = 1;
        trucoAtivo = false;
        ultimaATrucar = null;

        boolean maoDeDeZ = dupla1.estaNaMaoDeDez() || dupla2.estaNaMaoDeDez();
        boolean ambasCom10 = dupla1.estaNaMaoDeDez() && dupla2.estaNaMaoDeDez();

        if (maoDeDeZ) {
            System.out.println("\nMAO DE DEZ!");
            if (ambasCom10) {
                System.out.println("Ambas as duplas têm 10 pontos! Mão será disputada sem recursos.");
            } else {
                System.out.println("Não é permitido trucar nesta mão!");

                Dupla duplaCom10 = dupla1.estaNaMaoDeDez() ? dupla1 : dupla2;
                System.out.println("\n" + duplaCom10.getNome() + " pode consultar entre parceiros.");
                System.out.println("Desejam desistir da mão? (s/n)");
                String resposta = scanner.nextLine().toLowerCase().trim();

                if (resposta.equals("s") || resposta.equals("sim")) {
                    System.out.println(duplaCom10.getNome() + " desistiu da mão!");
                    Dupla duplaAdversaria = duplaCom10 == dupla1 ? dupla2 : dupla1;
                    duplaAdversaria.adicionarPontos(1);
                    System.out.println(duplaAdversaria.getNome() + " ganhou 1 ponto!");
                    return;
                }
            }
        }

        baralho.resetarBaralho();
        List<Jogador> todosJogadores = new ArrayList<>();
        todosJogadores.addAll(dupla1.getJogadores());
        todosJogadores.addAll(dupla2.getJogadores());

        for (Jogador jogador : todosJogadores) {
            jogador.receberCartas(baralho.distribuirMao());
        }

        int vitoriasD1 = 0, vitoriasD2 = 0, empates = 0;
        boolean[] resultadoVazas = new boolean[3];

        for (int vaza = 0; vaza < 3; vaza++) {
            System.out.println("\n--- Vaza " + (vaza + 1) + " ---");
            System.out.println("Valor da mão: " + valorMao + " ponto(s)");

            boolean podeTrucar = !maoDeDeZ || ambasCom10;
            int resultadoVaza = jogarVaza(vaza, podeTrucar);

            if (resultadoVaza == 1) {
                vitoriasD1++;
                resultadoVazas[vaza] = true;
            } else if (resultadoVaza == 2) {
                vitoriasD2++;
                resultadoVazas[vaza] = false;
            } else {
                empates++;
            }

            if (vitoriasD1 >= 2 || vitoriasD2 >= 2) break;
            if (vaza == 1 && vitoriasD1 == 1 && empates == 1) {
                System.out.println("Dupla 1 vence (ganhou primeira e empatou segunda)!");
                vitoriasD1 = 2;
                break;
            }
            if (vaza == 1 && vitoriasD2 == 1 && empates == 1) {
                System.out.println("Dupla 2 vence (ganhou primeira e empatou segunda)!");
                vitoriasD2 = 2;
                break;
            }
        }

        Dupla vencedoraMao = null;
        if (vitoriasD1 > vitoriasD2) {
            vencedoraMao = dupla1;
        } else if (vitoriasD2 > vitoriasD1) {
            vencedoraMao = dupla2;
        } else if (empates == 3) {
            vencedoraMao = dupla2;
        }

        if (vencedoraMao != null) {
            int pontosGanhos = valorMao;

            if (maoDeDeZ && !ambasCom10) {
                Dupla duplaSem10 = dupla1.estaNaMaoDeDez() ? dupla2 : dupla1;
                if (vencedoraMao == duplaSem10) {
                    pontosGanhos = 3;
                    System.out.println("Dupla sem 10 pontos ganhou a Mão de Dez! Recebe 3 pontos!");
                }
            }

            vencedoraMao.adicionarPontos(pontosGanhos);
            System.out.println("\n" + vencedoraMao.getNome() + " ganhou a mão e " + pontosGanhos + " ponto(s)!");
        }
    }

    private int jogarVaza(int numeroVaza, boolean podeTrucar) {
        List<Carta> cartasJogadas = new ArrayList<>();
        List<Jogador> jogadoresEstaVaza = new ArrayList<>();

        for (int i = 0; i < 4; i++) {
            int indice = (indiceProximoJogador + i) % 4;
            jogadoresEstaVaza.add(ordemJogadores.get(indice));
        }

        for (int i = 0; i < jogadoresEstaVaza.size(); i++) {
            Jogador jogador = jogadoresEstaVaza.get(i);

            if (podeTrucar && podeOferecerrTruco(jogador)) {
                if (oferecerTruco(jogador)) {
                    Jogador proximoAdversario = encontrarProximoAdversario(jogadoresEstaVaza, i, jogador);
                    Dupla duplaQueRecusou = processarTrucoCompleto(jogador, proximoAdversario);
                    if (duplaQueRecusou != null) {
                        Dupla vencedora = getDuplaDoJogador(jogador);
                        return vencedora == dupla1 ? 1 : 2;
                    }
                    podeTrucar = false;
                }
            }

            Carta carta = jogador.escolherCarta(cartasJogadas, false);
            cartasJogadas.add(carta);

            System.out.println(jogador.getNome() + " jogou: " + carta);
        }

        Carta cartaVencedora = Collections.max(cartasJogadas);
        int indiceVencedor = cartasJogadas.indexOf(cartaVencedora);
        Jogador jogadorVencedor = jogadoresEstaVaza.get(indiceVencedor);

        Dupla duplaVencedora = getDuplaDoJogador(jogadorVencedor);

        long cartasMaximas = cartasJogadas.stream()//faz a contagem dentro da lista de cartas para ver a mais forte
                .mapToInt(Carta::getForcaEfetiva)
                .filter(f -> f == cartaVencedora.getForcaEfetiva())
                .count();

        if (cartasMaximas > 1) {
            System.out.println("Vaza empatada!");
            return 0;
        }

        System.out.println("Vaza ganha por " + duplaVencedora.getNome() + " (" + jogadorVencedor.getNome() + ")!");

        indiceProximoJogador = ordemJogadores.indexOf(jogadorVencedor);

        return duplaVencedora == dupla1 ? 1 : 2;
    }

    private Jogador encontrarProximoAdversario(List<Jogador> ordemJogadores, int indiceAtual, Jogador jogadorQueTrucou) {
        Dupla duplaDoJogador = getDuplaDoJogador(jogadorQueTrucou);

        for (int i = indiceAtual + 1; i < ordemJogadores.size(); i++) {
            Jogador candidato = ordemJogadores.get(i);
            if (getDuplaDoJogador(candidato) != duplaDoJogador) {
                return candidato;
            }
        }

        for (int i = 0; i < indiceAtual; i++) {
            Jogador candidato = ordemJogadores.get(i);
            if (getDuplaDoJogador(candidato) != duplaDoJogador) {
                return candidato;
            }
        }

        return null;
    }

    private boolean podeOferecerrTruco(Jogador jogador) {
        if (!(jogador instanceof JogadorHumano)) {
            return false;
        }

        Dupla duplaDoJogador = getDuplaDoJogador(jogador);

        boolean maoDeDeZ = dupla1.estaNaMaoDeDez() || dupla2.estaNaMaoDeDez();
        boolean ambasCom10 = dupla1.estaNaMaoDeDez() && dupla2.estaNaMaoDeDez();

        if (maoDeDeZ && !ambasCom10) {
            Dupla duplaCom10 = dupla1.estaNaMaoDeDez() ? dupla1 : dupla2;
            if (duplaDoJogador == duplaCom10) {
                System.out.println("ATENCAO: Se sua dupla trucar na Mão de Dez, vocês perderão a mão automaticamente!");
            }
        }

        if (ultimaATrucar == null) {
            return true;
        }

        return ultimaATrucar != duplaDoJogador;
    }

    private boolean oferecerTruco(Jogador jogador) {
        System.out.println("\n--- Vez de " + jogador.getNome() + " ---");
        System.out.println("Suas cartas: " + jogador.getMao());

        String opcaoTruco = getProximaOpcaoTruco();
        if (opcaoTruco.equals("NENHUMA")) {
            return false;
        }

        System.out.println("Deseja " + opcaoTruco.toLowerCase() + "? (s/n)");
        String resposta = scanner.nextLine().toLowerCase().trim();

        boolean maoDeDeZ = dupla1.estaNaMaoDeDez() || dupla2.estaNaMaoDeDez();
        boolean ambasCom10 = dupla1.estaNaMaoDeDez() && dupla2.estaNaMaoDeDez();

        if ((resposta.equals("s") || resposta.equals("sim")) && maoDeDeZ && !ambasCom10) {
            Dupla duplaDoJogador = getDuplaDoJogador(jogador);
            Dupla duplaCom10 = dupla1.estaNaMaoDeDez() ? dupla1 : dupla2;

            if (duplaDoJogador == duplaCom10) {
                System.out.println(duplaDoJogador.getNome() + " trucou na Mão de Dez e perdeu a mão!");
                Dupla duplaAdversaria = duplaCom10 == dupla1 ? dupla2 : dupla1;
                duplaAdversaria.adicionarPontos(3);
                System.out.println(duplaAdversaria.getNome() + " ganhou 3 pontos!");
                return false;
            }
        }
        return resposta.equals("s") || resposta.equals("sim");
    }

    private String getProximaOpcaoTruco() {
        if (!trucoAtivo) {
            return "trucar";
        }

        switch (valorMao) {
            case 3:
                return "pedir 6";
            case 6:
                return "pedir 9";
            case 9:
                return "pedir 12";
            case 12:
                return "NENHUMA";
            default:
                return "NENHUMA";
        }
    }

    private Dupla processarTrucoCompleto(Jogador jogadorQueTrucou, Jogador jogadorQueDecide) {
        int valorOriginal = valorMao;
        String opcaoTruco = getProximaOpcaoTruco();
        int novoValor = getNovoValorMao();

        System.out.println("\n" + jogadorQueTrucou.getNome() + " pediu para " + opcaoTruco + "!");

        System.out.println("\n--- " + jogadorQueDecide.getNome() + ", você aceita " + opcaoTruco + "? ---");
        System.out.println("Suas cartas: " + jogadorQueDecide.getMao());
        System.out.println("Valor atual da mão: " + valorOriginal + " ponto(s)");
        System.out.println("Novo valor se aceitar: " + novoValor + " ponto(s)");

        if (jogadorQueDecide instanceof JogadorHumano) {
            System.out.println("Opções:");
            System.out.println("1. Aceitar " + opcaoTruco);
            System.out.println("2. Recusar " + opcaoTruco);

            String proximaOpcaoTruco = getProximaOpcaoTrucoApos(novoValor);
            if (!proximaOpcaoTruco.equals("NENHUMA")) {
                System.out.println("3. " + proximaOpcaoTruco);
            }

            System.out.print("Escolha (1/2" + (!proximaOpcaoTruco.equals("NENHUMA") ? "/3" : "") + "): ");
            String resposta = scanner.nextLine().trim();

            switch (resposta) {
                case "1":
                    System.out.println(jogadorQueDecide.getNome() + " aceitou " + opcaoTruco + "!");
                    valorMao = novoValor;
                    trucoAtivo = true;
                    ultimaATrucar = getDuplaDoJogador(jogadorQueTrucou);
                    return null;

                case "2":
                    System.out.println(jogadorQueDecide.getNome() + " recusou " + opcaoTruco + "!");
                    System.out.println(getDuplaDoJogador(jogadorQueTrucou).getNome() + " ganha a mão!");
                    return getDuplaDoJogador(jogadorQueDecide);

                case "3":
                    if (!proximaOpcaoTruco.equals("NENHUMA")) {
                        System.out.println(jogadorQueDecide.getNome() + " " + proximaOpcaoTruco + "!");
                        valorMao = novoValor;
                        trucoAtivo = true;
                        ultimaATrucar = getDuplaDoJogador(jogadorQueDecide);

                        return processarTrucoCompleto(jogadorQueDecide, jogadorQueTrucou);
                    }
                    System.out.println("Opção inválida. Considerando como recusa.");
                    System.out.println(getDuplaDoJogador(jogadorQueTrucou).getNome() + " ganha a mão!");
                    return getDuplaDoJogador(jogadorQueDecide);

                default:
                    System.out.println("Opção inválida. Considerando como recusa.");
                    System.out.println(getDuplaDoJogador(jogadorQueTrucou).getNome() + " ganha a mão!");
                    return getDuplaDoJogador(jogadorQueDecide);
            }
        } else {
            return getDuplaDoJogador(jogadorQueDecide);
        }
    }

    private String getProximaOpcaoTrucoApos(int valorApos) {
        switch (valorApos) {
            case 3:
                return "pedir 6";
            case 6:
                return "pedir 9";
            case 9:
                return "pedir 12";
            default:
                return "NENHUMA";
        }
    }

    private int getNovoValorMao() {
        if (!trucoAtivo) {
            return 3;
        }

        switch (valorMao) {
            case 3: return 6;
            case 6: return 9;
            case 9: return 12;
            default: return valorMao;
        }
    }

    private Dupla getDuplaDoJogador(Jogador jogador) {
        if (dupla1.getJogadores().contains(jogador)) {
            return dupla1;
        } else if (dupla2.getJogadores().contains(jogador)) {
            return dupla2;
        }
        return null;
    }

    private void mostrarPlacar() {
        System.out.println("\n=== PLACAR DA QUEDA ===");
        System.out.println(dupla1.getNome() + ": " + dupla1.getJogosGanhos() + " jogos, " + dupla1.getPontos() + " pontos");
        System.out.println(dupla2.getNome() + ": " + dupla2.getJogosGanhos() + " jogos, " + dupla2.getPontos() + " pontos");

        if (dupla1.estaNaMaoDeDez()) {
            System.out.println(dupla1.getNome() + " está na MAO DE DEZ!");
        }
        if (dupla2.estaNaMaoDeDez()) {
            System.out.println(dupla2.getNome() + " está na MAO DE DEZ!");
        }
    }

    private void verEstatisticas() {
        if (duplas.isEmpty()) {
            System.out.println("Nenhuma dupla cadastrada.");
            return;
        }

        System.out.println("\n=== ESTATÍSTICAS DAS DUPLAS ===");
        for (Dupla dupla : duplas) {
            System.out.println(dupla.toStringDetalhado());
            System.out.println("---");
        }
    }

    private void carregarDados() {
        try {
            File arquivoJogadores = new File(ARQUIVO_JOGADORES);
            if (arquivoJogadores.exists()) {
                Scanner fileScanner = new Scanner(arquivoJogadores);
                while (fileScanner.hasNextLine()) {
                    String linha = fileScanner.nextLine();
                    String[] partes = linha.split(",");
                    if (partes.length >= 3) {
                        String nome = partes[0];
                        String tipo = partes[1];
                        int id = Integer.parseInt(partes[2]);
                        if ("HUMANO".equals(tipo)) {
                            jogadores.add(new JogadorHumano(nome, id));
                        }
                    }
                }
                fileScanner.close();
            }
            List<Dupla> duplasSalvas = Dupla.carregarDuplas(ARQUIVO_DUPLAS);
            for (Dupla dupla : duplasSalvas) {
                if (!duplas.stream().anyMatch(d -> d.getId() == dupla.getId())) {
                    duplas.add(dupla);
                }
            }
            System.out.println("Dados carregados com sucesso.");
        } catch (IOException e) {
            System.out.println("Arquivo de dados não encontrado. Iniciando com dados vazios.");
        }
    }

    private void salvarDados() throws IOException {
        try (FileWriter writer = new FileWriter(ARQUIVO_DUPLAS)) {
            for (Dupla dupla : duplas) {
                writer.write(dupla.toString() + "\n");
            }
        }
        try (FileWriter writer = new FileWriter(ARQUIVO_JOGADORES)) {
            for (Jogador jogador : jogadores) {
                writer.write(jogador.getNome() + ",HUMANO," + jogador.getId() + "\n");
            }
        }
        System.out.println("Dados salvos com sucesso.");
    }

    private void salvarEstatisticas() throws IOException {
        try (FileWriter writer = new FileWriter(ARQUIVO_ESTATISTICAS, true)) {
            writer.write("=== RESULTADO DA QUEDA ===\n");
            writer.write(dupla1.toString() + "\n");
            writer.write(dupla2.toString() + "\n");
            writer.write("Vencedor: " + (dupla1.ganhouQueda() ? dupla1.getNome() : dupla2.getNome()) + "\n");
            writer.write("---\n");
        }
    }
}