process.stdout.write("Witaj!\nPodaj imię i nazwisko: ");

process.stdout.on('data', function(data){
    process.stdout.write("Twoje imię i nazwisko: " + data);
    process.exit();
})

process.on('exit', function(){
    process.stdout.write("Żegnaj\n");
})
