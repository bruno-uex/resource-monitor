# Script auxiliar para visualização de métricas (exemplo)
import sys
import pandas as pd
import matplotlib.pyplot as plt

def main():
    if len(sys.argv) < 2:
        print("Uso: python visualize.py <arquivo.csv>")
        return
    df = pd.read_csv(sys.argv[1])
    df.plot()
    plt.show()

if __name__ == "__main__":
    main()
