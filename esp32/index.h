const char INDEX_HTML[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Mão Robótica</title>
    <style>
        :root {
            --fundo: #f2f2f2;
            --especial: #99A6BF;
            --texto: #304F8C;
            font-family: sans-serif;
        }
        
        body {
            margin: 0;
            background-color: var(--fundo);
        }
        #nuvem-esquerda {
            position: absolute;
            top: 0;
        }
        #nuvem-direita {
            position: absolute;
            bottom: 0;
            right: 0;
        }
        #gear {
            position: absolute;
            bottom: 0;
            left: 0;
        }
        #vitrines {
            position: absolute;
            top: 0;
            right: 0;
            pointer-events: none;
        }
        #letras, #numeros, #exp  {
            display: none;
        }
        #botao{
            display: flex;
        }
        .logo {
            width: 15%;
        }
        #botao, #letras, #numeros, #exp, #inicio, #camera{
            flex-direction: column;
            align-items: center;
            justify-content: center;
        }
        
        h1 {
            margin-bottom: 0;
            color: var(--especial);
        }
        p {
            margin-top: 0.3em;
            color: var(--texto);
            font-weight: bold;
        }
        .bot {
            font-size: 3em;
            color: var(--texto);
            background: var(--especial);
            box-shadow: 5px 6px 4px rgba(0, 0, 0, 0.25);
            border-radius: 3px;
            border: none;
            font-weight: bold;
            padding: 0.25em;
            cursor: pointer;
        }
        #botao > button {
            margin: 1.5%;
        }
        #inicio > button{
            margin: 2%;
        }
        main {
            display: flex;
            flex-direction: column;
            border: 4px solid #304F8C;
            border-radius: 4px;
        }
        section {
            display: flex;
            flex-direction: row;
            justify-content: space-around;
        }
        fieldset{
            display: flex;
            border: 4px solid #304F8C;
            border-radius: 4px;
        }
        section:not(:last-child) {
            padding-bottom: 10%;
        }
        section > button, main > button {
            border: none;
            background-color: transparent;
            color: var(--texto);
            font-weight: bold;
            font-size: 3em;
            cursor: pointer;
        }
        p.resposta {
            font-size: 2em;
        }
        .voltar {
            cursor: pointer;
            margin-top: 10px;
            width: 100;
        }
        footer {
            position: absolute;
            bottom: 0px;
            width: 100%;
        }
        
        footer > p {
            text-align: center;
            text-transform: uppercase;
            color: var(--texto);
            font-weight: bold;
            opacity: 55%;
        }
        @media screen and (orientation: landscape) {
            h1 {
                font-size: 6em;
            }

            #inicio > p, #botao > p {
                font-size: 1.5em;
            }
        
            main {
                width: 25%;
            }
        }
        @media screen and (orientation: portrait) {
            #gear {
                display: none;
            }
            #vitrines {
                display: none;
            }
            .logo {
                margin-top: 15%;
                width: 50%;
            }
            h1 {
                margin-top: 2em;
                font-size: 3em;
            }
            p {
                font-size: 1em;
            }
            footer {
                margin-bottom: 5%;
            }
            footer > p {
                margin-left: 10%;
                margin-right: 15%;
                margin-bottom: 8%;
            }
        }
    </style>
</head>
<body>
    <svg id="nuvem-esquerda" width="232" height="81" viewBox="0 0 232 81" fill="none" xmlns="http://www.w3.org/2000/svg">
        <path d="M119.372 47.2554C155.521 56.6594 208.186 7.00347 230 -19H-38V47.2554C-31.7674 91.7107 30.0388 81.4518 60.1628 70.7654C100.051 89.5734 116.256 62.9287 119.372 47.2554Z" fill="#274073" stroke="black"/>
    </svg>
    <svg id="nuvem-direita" width="195" height="243" viewBox="0 0 195 243" fill="none" xmlns="http://www.w3.org/2000/svg">
        <path d="M166.35 125.225C140.954 79.645 184.868 24.0833 210 2V267H1.00966C-0.0485202 209.76 86.1049 193.683 129.314 192.8C118.732 164.18 149.596 135.825 166.35 125.225Z" fill="#274073" stroke="black"/>
    </svg>
    <img id="gear" src="https://raw.githubusercontent.com/ryancosta15/TCC-IFRJ-CNIT/598746a2f4f15f698d6abca66ecdb266c1af1212/web/src/gear.svg" alt="">
    <img id="vitrines" src="https://raw.githubusercontent.com/ryancosta15/TCC-IFRJ-CNIT/main/web/src/vitrines.png" alt="">

    <div id="botao">
        <img src="https://raw.githubusercontent.com/ryancosta15/TCC-IFRJ-CNIT/main/web/src/logo.png" alt="logo mão" class="logo">
        <p>ESCOLHA O SINAL QUE SUA MÃO FARÁ</p>
        <button onclick="guia('#letras')" class="bot">LETRAS</button>
        <button onclick="guia('#numeros')" class="bot">NÚMEROS</button>
        <button onclick="guia('#exp')" class="bot" id="ultb">EXPRESSÕES</button>
    </div>
    <div id="letras">
        <h1>LETRAS</h1>
        <main>
            <section>
                <button>C</button>
                <button>L</button>
                <button>Y</button>
            </section>
        </main>
        <svg onclick="guia('#botao')"class="voltar" width="134" height="136" viewBox="0 0 134 136" fill="none">
            <rect x="1" y="2" width="133" height="134" rx="66.5" fill="white"/>
            <path d="M1 2.00251C116 1.49179 159.5 79.5 35.4999 94.0025M35.4999 94.0025L45.4999 74.0027M35.4999 94.0025L50.9999 105.503" stroke="#092C73" stroke-width="4"/>
        </svg>
        <p class="resposta"></p>
    </div>
    <div id="numeros">
        <h1>NÚMEROS</h1>
        <main>
            <section>
                <button>0</button>
                <button>1</button>
                <button>2</button>
                <button>3</button>
            </section>
            <section>
                <button>4</button>
                <button>5</button>
                <button>-</button>
                <button>-</button>
            </section>  
        </main>
        <svg onclick="guia('#botao')"class="voltar" width="134" height="136" viewBox="0 0 134 136" fill="none">
            <rect x="1" y="2" width="133" height="134" rx="66.5" fill="white"/>
            <path d="M1 2.00251C116 1.49179 159.5 79.5 35.4999 94.0025M35.4999 94.0025L45.4999 74.0027M35.4999 94.0025L50.9999 105.503" stroke="#092C73" stroke-width="4"/>
        </svg>
        <p class="resposta"></p>
    </div>
    <div id="exp">
        <h1>EXPRESSÕES</h1>
        <main>
            <button>Tchau</button>
        </main>
        <svg onclick="guia('#botao')"class="voltar" width="134" height="136" viewBox="0 0 134 136" fill="none">
            <rect x="1" y="2" width="133" height="134" rx="66.5" fill="white"/>
            <path d="M1 2.00251C116 1.49179 159.5 79.5 35.4999 94.0025M35.4999 94.0025L45.4999 74.0027M35.4999 94.0025L50.9999 105.503" stroke="#092C73" stroke-width="4"/>
        </svg>
        <p class="resposta"></p>
    </div>
    <footer>
        <p>Feito por Rafael Cunha, Ryan Costa, João Pedro Gonçalves e Caio Lopes</p>
        <p id="ultimo">IFRJ - Campus Niterói</p>
    </footer>
    <script>
        const PAGINAS = ["#botao", "#letras", "#numeros", "#exp"]
        let textosResposta = document.querySelectorAll("p.resposta")
        function guia(op) {
            PAGINAS.forEach((pagina) => {
                document.querySelector(pagina).style.display = "none"
            })
            document.querySelector(op).style.display = "flex"
        }
        let botoes = document.querySelectorAll("button:not(button[onclick])")
        async function on(pagina) {
            textosResposta.forEach(elemento => elemento.innerHTML = "Fazendo pedido... Aguarde")
            console.log("/on" + pagina)
            const resposta = await fetch("/on" + pagina)
            .then(resposta => {
                const dados = resposta
                console.log(dados)
                textosResposta.forEach(elemento => elemento.innerHTML = "Pedido feito!")
            })
            .catch(erro => {
                textosResposta.forEach(elemento => elemento.innerHTML = "Erro, verifique sua conexão com o servidor")
            });
            botoes.forEach(elemento => elemento.style.color = "var(--texto)")
        }
        botoes.forEach((elemento) => {
            elemento.style.color = "var(--texto)"
            elemento.addEventListener("click", () => {
                if (elemento.style.color == "var(--texto)") {
                    botoes.forEach(elemento => elemento.style.color = "rgba(240, 248, 255, 0.534)")
                    elemento.style.color = "#304F8C"
                    on(elemento.innerHTML) // Futuro tratamento de espaços no caso de erro com páginas do esp32
                } else {
                    textosResposta.forEach(elemento => elemento.innerHTML = "Espere!")
                }
            })
        })
    </script>
</body>
</html>

)=====";