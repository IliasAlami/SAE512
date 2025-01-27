<?php
include 'db.php';

// Requête pour récupérer les 5 dernières mesures de température
$query = 'from(bucket: "Donnees_SolarEdge")
    |> range(start: -20y)
    |> filter(fn: (r) => r["_measurement"] == "puissance_mois")
    |> sort(columns: ["_time"], desc: true)
    |> limit(n: 1)';

try {
    $result = $client->createQueryApi()->query($query);
    $puissance_mois = [];
    foreach ($result as $table) {
        foreach ($table->records as $record) {
            $puissance_mois[] = [
                'heure' => $record->getTime(),
                'puissance_mois' => $record->getValue()
            ];
        }
    }
} catch (Exception $e) {
    die("Erreur : " . $e->getMessage());
}

?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Mesures de puissance par mois</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <header>
        <nav>
            <ul>
                <li><a href="index.php">Accueil</a></li>
                <li><a href="temperature.php" class="active">Température</a></li>
                <li><a href="lumiere.php">Lumière</a></li>
	        <li><a href="liste_puissance.html">Puissance</a></li>
	        <li><a href="services.html">Nos services</a></li>
            </ul>
        </nav>
    </header>

    <main>
        <h1>Mesure du dernier mois</h1>
        <table>
            <thead>
                <tr>
                    <th>Heure</th>
                    <th>Puissance  (Watt)</th>
                </tr>
            </thead>
            <tbody>
                <?php foreach ($puissance_mois as $row): ?>
                <tr>
                    <td><?= date("Y-m-d H:i:s", strtotime($row['heure'])) ?></td>
                    <td><?= $row['puissance_mois'] ?> W</td>
                </tr>
                <?php endforeach; ?>
            </tbody>
        </table>
    </main>
</body>
</html>
