# Module Alim / Chargeur de batterie

## Liste des composants :

- battery charger: [Max integrated MAX1555EZK+T](https://www.mouser.ch/ProductDetail/Maxim-Integrated/MAX1555EZK%2bT?qs=LHmEVA8xxfYLEoVKeceKJA%3D%3D) 

- Régulateurs de tension :
  
  - [Microship MCP1643 (en MSOP-8): Step-up 5V](https://www.mouser.ch/datasheet/2/268/20005208A-268812.pdf)
  
  - [LM3671MF-3.3/NOPB: step-down to 3.3V](https://www.mouser.ch/ProductDetail/Texas-Instruments/LM3671MF-3.3-NOPB?qs=QbsRYf82W3E7NHceZ4TukA%3D%3D)

Les versions avec une seule sortie me semblent plus simple pour le montage.  

- USB C :
  - power : VBUS et GND pins. VBUS est par défault à 5V. Les pins CC sont utilisés pour négocier la tension voulue: `request`, `power supply ready` messages.€

l
