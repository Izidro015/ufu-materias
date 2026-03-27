import java.util.List;

interface AcoesJogador {
    Carta escolherCarta(List<Carta> vazaAtual, boolean podeTrucar);
    boolean aceitarTruco(int valorAtual);
    boolean querTrucar(List<Carta> mao, List<Carta> vazaAtual);
    void receberCartas(List<Carta> cartas);
}
