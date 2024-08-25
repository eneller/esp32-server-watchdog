use std::{thread, io};
use std::time::Duration;
use serialport::{available_ports, SerialPort, SerialPortType};

const HEARTBEAT_INTERVAL: Duration = Duration::from_secs(5);
const HEARTBEAT_MESSAGE: &str = "OK";


fn main() {
    repeat(setup());
}

fn setup() -> Box<dyn SerialPort>{
    //TODO find serial port of microcontroller
    let port = serialport::new("/dev/pts/4", 9600)
        .open()
        .expect("Failed to open port");
    return port;

}
fn repeat(mut port:Box<dyn SerialPort>){
    loop {
        match port.write(HEARTBEAT_MESSAGE.as_bytes()) {
            Ok(bytes) => (),
            // TODO log timeout error?
            Err(ref e) if e.kind() == io::ErrorKind::TimedOut => (),
            Err(e) => eprintln!("{:?}", e),
        }
        thread::sleep(HEARTBEAT_INTERVAL);
    }
}
