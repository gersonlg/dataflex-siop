/MENSAGEM_MES_SELECIONADO_NAO_ARMAZENADO
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³                          A T E N C A O  !!!                                ³
³                                                                            ³
³    Mes selecionado ainda nao armazenado no TCE, deseja prosseguir com a    ³
³    emissao ?  <S/N>                                                        ³
³                                                                            ³
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
/MENSAGEM_MES_13_NAO_ARMAZENADO
ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
³                          A T E N C A O  !!!                                ³
³                                                                            ³
³ Mes 13 ainda nao armazenado no TCE, deseja prosseguir com a emissao ? <S/N>³
³                                                                            ³
³                                                                            ³
ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
/*

PAGE SET MENSAGEM_MES_SELECIONADO_NAO_ARMAZENADO AT 10 01 COLORS IT_COR_TARJA  IT_COR_TITULO
PAGE SET MENSAGEM_MES_13_NAO_ARMAZENADO          AT 10 01 COLORS IT_COR_TARJA  IT_COR_TITULO

IF ((JN_COD_ENTIDADE EQ PARGERAL.COD_ENTIDADE) OR (JN_COD_ENTIDADE EQ '')) BEGIN
                                                                            //--verifica se mes esta fechado e com balanco gerado
                                                                            INDICATE @MES_ARMAZENADO! FALSE
                                                                            INDICATE         @M13!! FALSE

                                                                            CLEAR ENCERRA
                                                                            MOVE ST@CODIGO@ENTIDADE TO ENCERRA.COD_ENTIDADE
                                                                            MOVE PARGERAL.EXERCICIO TO ENCERRA.ANO
                                                                            MOVE JN_MES_FINAL       TO ENCERRA.MES
                                                                            FIND EQ ENCERRA BY INDEX.1
                                                                            [ FOUND] BEGIN
                                                                                      IF PARGERAL.ESTADO EQ 'SP' INDICATE @MES_ARMAZENADO! AS ENCERRA.ID_CONTABIL  NE ''
                                                                                      IF PARGERAL.ESTADO EQ 'MG' INDICATE @MES_ARMAZENADO! AS ENCERRA.ID_BALANCETE NE ''
                                                                                     END

                                                                            [ @MES_ARMAZENADO!] BEGIN
                                                                                                 IF JN_MES_FINAL EQ '12' BEGIN
                                                                                                                          CLEAR ENCERRA
                                                                                                                          MOVE ST@CODIGO@ENTIDADE TO ENCERRA.COD_ENTIDADE
                                                                                                                          MOVE PARGERAL.EXERCICIO TO ENCERRA.ANO
                                                                                                                          MOVE '13'               TO ENCERRA.MES
                                                                                                                          FIND EQ ENCERRA BY INDEX.1
                                                                                                                          [ FOUND] BEGIN
                                                                                                                                    IF ((PARGERAL.ESTADO EQ 'SP') AND (ENCERRA.ID_CONTABIL EQ '')) BEGIN
                                                                                                                                                                                                    INDICATE @MES_ARMAZENADO! FALSE
                                                                                                                                                                                                    INDICATE           @M13!! TRUE
                                                                                                                                                                                                   END
                                                                                                                                    IF ((PARGERAL.ESTADO EQ 'MG') AND (ENCERRA.ID_BALANCETE EQ '')) BEGIN
                                                                                                                                                                                                     INDICATE @MES_ARMAZENADO! FALSE
                                                                                                                                                                                                     INDICATE           @M13!! TRUE
                                                                                                                                                                                                    END
                                                                                                                                   END
                                                                                                                         END
                                                                                                END

                                                                            [~@MES_ARMAZENADO!] BEGIN
                                                                                                 [~@M13!!] PAGE MENSAGEM_MES_SELECIONADO_NAO_ARMAZENADO
                                                                                                 [ @M13!!] PAGE MENSAGEM_MES_13_NAO_ARMAZENADO
                                                                                                 
                                                                                                 INKEYCHECK ST_TECLA IN 'SsNn'
                                                                                                 IF ST_TECLA IN 'Nn' ABORT
                                                                                                 MOVE 0 TO CURRENT_IMAGE
                                                                                                 PAGE TELA
                                                                                                END
                                                                           END
//--
