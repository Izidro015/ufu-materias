import java.util.*;

abstract class Jogador implements AcoesJogador {
    protected String nome;
    protected List<Carta> mao;
    protected int id;

    public Jogador(String nome, int id) {
        this.nome = nome;
        this.id = id;
        this.mao = new ArrayList<>();
    }

    @Override
    public void receberCartas(List<Carta> cartas) {
        this.mao = new ArrayList<>(cartas);
        Collections.sort(this.mao, Collections.reverseOrder());
    }

    public void removerCarta(Carta carta) {
        mao.remove(carta);
    }

    public List<Carta> getMao() {
        return new ArrayList<>(mao);
    }

    public String getNome() {
        return nome;
    }

    public int getId() {
        return id;
    }
}
