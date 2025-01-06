// Fetch alerts and animate them
const alertsContainer = document.getElementById('alerts-container');

function fetchAlerts() {
    const alerts = [
        { type: 'Température', message: 'Seuil dépassé à X°C' },
        { type: 'Humidité', message: 'Seuil dépassé à X%' },
    ];

    alertsContainer.innerHTML = '';
    alerts.forEach((alert, index) => {
        const alertElement = document.createElement('div');
        alertElement.textContent = `${alert.type} : ${alert.message}`;
        alertElement.style.animationDelay = `${index * 0.2}s`;
        alertsContainer.appendChild(alertElement);
    });
}

// Update alerts every 10 seconds
setInterval(fetchAlerts, 10000);

// Button animation for download
const downloadButton = document.getElementById('download-historique');

downloadButton.addEventListener('click', () => {
    alert('Téléchargement de l\'historique en cours...');
    downloadButton.style.transform = 'scale(1.2)';
    setTimeout(() => {
        downloadButton.style.transform = 'scale(1)';
    }, 200);
});

// Initial call to populate alerts
fetchAlerts();
