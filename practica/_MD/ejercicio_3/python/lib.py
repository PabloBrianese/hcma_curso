def get_filepath(temperature, volume, sufix):
  from glob import glob
  folder = f"../DatosArgonLJ_Temp{temperature}_Vol{volume}/"
  filepath = glob(folder + '*' + sufix)[0]

  return filepath


from pandas import read_csv


def get_thermodinamic_df(filepath):
  return read_csv(
    filepath,
    sep=' ',
    header=None,
    skiprows=1,
    names=[
      'tiempo [fms]',
      'Temperatura [K]',
      'EnergiaTotal [Kcal/mol]',
      'EnergiaCineticaTotal [Kcal/mol]',
      'Presion [Atm]',
      'Volumen [ang**3]',
      'Densidad [g cm**-3]'
    ]
  )


def get_pressure(thermodinamic_df):
  return thermodinamic_df['Presion [Atm]'].mean()
