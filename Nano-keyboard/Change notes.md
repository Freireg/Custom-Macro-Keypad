# Self notes
- Adjust the charger module symbol (remove module)
- Adjust the LED footprint
- Include voltage step-up (charger module 18650) [https://produto.mercadolivre.com.br/MLB-1762665597-modulo-carregador-bateria-18650-step-up-ajustavel-45-a-24v-_JM?matt_tool=56291529&matt_word=&matt_source=google&matt_campaign_id=14303413604&matt_ad_group_id=133074303519&matt_match_type=&matt_network=g&matt_device=c&matt_creative=584156655498&matt_keyword=&matt_ad_position=&matt_ad_type=pla&matt_merchant_id=164968240&matt_product_id=MLB1762665597&matt_product_partition_id=1413191054866&matt_target_id=aud-532123542129:pla-1413191054866&gclid=CjwKCAjwwo-WBhAMEiwAV4dybdXkpld78MYYv50mU0W8G3eqyB_YherohOI6afGE0RhcUUI0lZDZPBoCVVMQAvD_BwE]
- Insert pinouts for battery, I2C, SPI, UART...
<!-- - See AMS1117 implementation -->
  <!-- - Vout = Vref*(1+R2/R1) (send Vref = 1,25V) -->
  <!-- - R1 = 600 ohms; R2 = 1k ohms -->
  <!-- - Add decoupling capacitor -->
<!-- - En Pull-up -->
- Add a button to En