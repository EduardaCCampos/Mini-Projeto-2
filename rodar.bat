@echo off
echo --- COMPILANDO O PROJETO ---
gcc main.c funcoes.c -o terrenos.exe

if %errorlevel% neq 0 (
    echo [ERRO] Falha na compilacao!
    pause
    exit /b
)

echo --- EXECUTANDO COM DADOS AUTOMATICOS ---
:: O comando abaixo deleta o banco de dados antigo para começar limpo
if exist dados.dat del dados.dat

:: Executa o programa injetando o input.txt
terrenos.exe dados.dat < input.txt

echo.
echo --- PROCESSO FINALIZADO ---
pause