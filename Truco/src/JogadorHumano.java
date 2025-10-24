import java.util.List;
import java.util.Scanner;

class JogadorHumano extends Jogador {
    private Scanner scanner;

    public JogadorHumano(String nome, int id) {
        super(nome, id);
        this.scanner = new Scanner(System.in);
    }

    @Override
    public Carta escolherCarta(List<Carta> vazaAtual, boolean podeTrucar) {
        System.out.println("\n" + nome + ", é sua vez!");
        mostrarMao();

        if (podeTrucar && !vazaAtual.isEmpty()) {
            System.out.print("Deseja trucar? (s/n): ");
            if (scanner.nextLine().toLowerCase().startsWith("s")) {
                System.out.println("Truco!");
            }
        }

        System.out.print("Escolha uma carta (1-" + mao.size() + "): ");
        try {
            int escolha = Integer.parseInt(scanner.nextLine()) - 1;
            if (escolha >= 0 && escolha < mao.size()) {
                Carta cartaEscolhida = mao.get(escolha);
                removerCarta(cartaEscolhida);
                return cartaEscolhida;
            }
        } catch (NumberFormatException e) {
            System.out.println("Entrada inválida!");
        }
        System.out.println("Jogando primeira carta disponível...");
        Carta carta = mao.get(0);
        removerCarta(carta);
        return carta;
    }

    @Override
    public boolean aceitarTruco(int valorAtual) {
        System.out.println("\n" + nome + ", adversário trucou!");
        System.out.println("Valor atual da mão: " + valorAtual + " pontos");
        mostrarMao();
        System.out.print("Aceitar truco? (s/n): ");
        return scanner.nextLine().toLowerCase().startsWith("s");
    }

    @Override
    public boolean querTrucar(List<Carta> mao, List<Carta> vazaAtual) {
        return false;
    }

    private void mostrarMao() {
        System.out.println("Suas cartas:");
        for (int i = 0; i < mao.size(); i++) {
            System.out.println((i + 1) + ". " + mao.get(i));
        }
    }
}
