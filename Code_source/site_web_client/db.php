<?php
require 'vendor/autoload.php'; // Assurez-vous que la bibliothèque InfluxDB PHP est installée

use InfluxDB2\Client;

$token = 'NUULqptTXN3jkZC3uzV5CNTGJvIcUK9uZsJr0zEkrhW8LnMjO-VX2kwFpYn7T29cLCDELZcjUNpeVvNTYAOuyQ=='; // Remplacez par votre jeton
$org = 'SAE512';    // Remplacez par le nom de votre organisation
$bucket = 'Donnees_SolarEdge';       // Remplacez par le nom de votre bucket
$url = 'http://localhost:8086'; // URL de votre instance InfluxDB

$client = new Client([
    "url" => $url,
    "token" => $token,
    "org" => $org,
    "bucket" => $bucket
]);

$query = 'from(bucket: "' . $bucket . '")
    |> range(start: -1h)';

try {
    $result = $client->createQueryApi()->query($query);
    /*echo "Connexion réussie. Données récupérées :<br>";
    foreach ($result as $table) {
        foreach ($table->records as $record) {
            echo $record->getTime() . " - " . $record->getValue() . "<br>";
        }
    }*/













} catch (Exception $e) {
    echo "Erreur : " . $e->getMessage();
}
?>
