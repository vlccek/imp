# Projekt do předmětu IMP - VUT FIT. 
Název projektu: `Š - ESP32 či jiný HW: Digitální FM rádio (modul RDA5807M a zesilovač PAM8407)`
# zadání

## Popis projektu:
S využitím libovolného vývojového kitu na bázi SoC ESP32 od společnosti Espressif a potřebných externích prvků realizujte koncept digitálního FM rádia s možností ladění rádiových stanic v pásmu 76MHz – až 108MHz FM. Výsledné zařízení sestávající se z potřebných hardwarových prvků a řídicího firmware by mělo nabídnou uživateli možnost naladění a poslech zvolené radio stanice v pásmu FM dle požadavků, včetně případného rozbraní RDS informací.

## Bližší specifikace:

S využitím mikrokontroléru na bázi SoC ESP32, modulu FM přijímače RDA5807M, modulu audio zesilovače PAM8407 třídy D s digitálním řízením hlasitosti a sady dvou reproduktorů realizujte koncept digitálního FM rádia. Nedílnou součástí řešení by mělo být i jednoduché uživatelské rozhraní realizované formou kombinace vhodného displeje a ovládacího prvku (např. tlačítka, rotační enkodér, detektor gest, a podobně).

Při řešení projektu můžete použít libovolné existující knihovny dle vlastního uvážení, přičemž nezapomeňte na jejich náležité ocitování v dokumentaci a na úrovni zdrojových kódů. Berte však v potaz skutečnost, že by měl být z výsledného řešení patrný i jistý objem vámi odvedené práce či implementačního úsilí. Pro realizaci projektu můžete použít libovolného programovacího jazyka a vývojového prostředí podporovaného na cílové platformě.

Volbu jiné než doporučované implementační platformy (tj. SoC ESP32 a kit Wemos D1 R32), odlišnosti oproti zadání projektu či upřesnění detailů řešení konzultujte prosím s vedoucím projektu. Vyčkejte prosím dalších instrukcí ohledně možnosti vyzvednutí si potřebného vybavení k řešení projektu!

## Dokumentace, odevzdání a hodnocení projektu:

Vytvořte přehlednou dokumentaci k přípravě, způsobu realizace, k funkčnosti a vlastnostem řešení projektu.
Řešení (projekt, bez binárních souborů sestavitelných na základě zdrojových souborů v projektu, a dokumentaci ve zdrojové i binární, tj. PDF, podobě)odevzdávejte prostřednictvím IS v jediném ZIP archívu.
Předvedení řešení se implicitně předpokládá v osobní podobě, s následným vrácením zapůjčeného vybavení. Pokud by, vzhledem k pandemickým či jiným okolnostem daným "vyšší mocí", osobní předvedení/vrácení nebylo možné, připravte se prosím na náhradní možnost - např. online/vzdálené předvedení přes Microsoft Teams, Google Meet apod., tvorbu krátkého videa demonstrujícího řešení, vrácení vybavení na vrátnici, u příležitosti zkoušky apod.
Podpůrné materiály k řešení projektu:

1.  [Schéma zapojení desky Wemos D1 R32](https://www.fit.vutbr.cz/~simekv/IMP_projekt_board_ESP32_Wemos_D1_R32.pdf)
2.  [Modul s OLED displejem 0,96", SPI rozhraní](https://www.hadex.cz/m508a-displej-oled-096-128x64-znaku-7pinu-bily/)
3.  [FM přijímač na bázi čipsetu RDA5807M](https://www.hadex.cz/m501a-fm-prijimac-pro-arduino-modul-rrd102-v20-io-rda5807m/)
4.  [Audio zesilovač PAM8407 třídy D](https://www.diodes.com/assets/Datasheets/products_inactive_data/PAM8407.pdf)
5.  [Schéma zapojení modulu s audio zesilovačem PAM8407](https://www.fit.vutbr.cz/~simekv/IMP_projekt_digitalni_radio_PAM8407_Module.pdf)
6.  [Modul s ovládacím prvkem - rotační enkodér KY-040](https://elty.pl/cs_CZ/p/Impulsni-modul-snimace-KY-040/1155)

## Hodocení: 
Dokumentace (až 4 b): 4

Funkčnost (až 5 b): 5

Prezentace (až 1 b): 1

Kvalita implementace (až 4 b): 4

**Celkem (až 14 b): 14.0**

Komentář: Velmi pěkné řešení. Vše je plně funkční a pečlivě zdokumentováno, i když někdo by se mohl eventuálně trošku ošívat nad rozsahem dokumentace. Nicméně soudím, že obsahuje vše potřebné. Uživatelské rozhraní je plně vyhovující. Coby bonus jste zprovoznil ovládání skrze webovou stránku (jako proof-of-concept je to v pohode, pro reálné použití by tento aspekt chtělo trošku doladit).
