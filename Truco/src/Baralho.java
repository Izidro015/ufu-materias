import java.util.*;

public class Baralho {
    private List<Carta> cartas;
    private Random random;

    public Baralho() {
        this.cartas = new ArrayList<>();
        this.random = new Random();
        inicializarBaralho();
    }

    private void inicializarBaralho() {
        cartas.clear();

        for (Carta.Naipe naipe : Carta.Naipe.values()) {
            for (Carta.Valor valor : Arrays.asList(
                    Carta.Valor.QUATRO, Carta.Valor.CINCO, Carta.Valor.SEIS, Carta.Valor.SETE,
                    Carta.Valor.DAMA, Carta.Valor.VALETE, Carta.Valor.REI, Carta.Valor.AS,
                    Carta.Valor.DOIS, Carta.Valor.TRES)) {

                if (isCartaValida(naipe, valor)) {
                    cartas.add(new Carta(naipe, valor));
                }
            }
        }
    }

    private boolean isCartaValida(Carta.Naipe naipe, Carta.Valor valor) {
        switch (valor) {
            case SETE:
                return naipe == Carta.Naipe.PAUS || naipe == Carta.Naipe.ESPADAS ||
                        naipe == Carta.Naipe.COPAS || naipe == Carta.Naipe.OUROS;
            case AS:
                return naipe == Carta.Naipe.PAUS || naipe == Carta.Naipe.COPAS ||
                        naipe == Carta.Naipe.OUROS || naipe == Carta.Naipe.ESPADAS;
            case QUATRO:
                return naipe == Carta.Naipe.COPAS || naipe == Carta.Naipe.ESPADAS ||
                        naipe == Carta.Naipe.OUROS || naipe == Carta.Naipe.PAUS;
            default:
                return true;
        }
    }

    public void embaralhar() {
        Collections.shuffle(cartas, random);
    }

    public Carta distribuirCarta() throws IllegalStateException {
        if (cartas.isEmpty()) {
            throw new IllegalStateException("Baralho vazio! Não é possível distribuir mais cartas.");
        }
        return cartas.remove(cartas.size() - 1);
    }

    public List<Carta> distribuirMao() throws IllegalStateException {
        List<Carta> mao = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            mao.add(distribuirCarta());
        }
        return mao;
    }

    public void resetarBaralho() {
        inicializarBaralho();
        embaralhar();
    }
}