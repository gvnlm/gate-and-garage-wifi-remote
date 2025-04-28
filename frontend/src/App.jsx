import arduinoService from './services/arduino';

const App = () => {
  return (
    <div>
      <button onClick={() => arduinoService.openGate()}>Open gate</button>
      <button onClick={() => arduinoService.openGarage()}>Open garage</button>
    </div>
  );
};

export default App;
